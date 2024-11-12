#include "icb_gui.h" 
#include <windows.h>
#include <thread>

ICBYTES panel;
int FRM1, BTN;
bool keypressed = false;

const int NUM_BOXES = 10;
const int NUM_BULLETS = 10;
const int BOX_WIDTH = 50;
const int BOX_HEIGHT = 40;


struct Box {
    int x, y;
    bool visible;
};

Box boxes[NUM_BOXES];
int bulletX[NUM_BULLETS], bulletY[NUM_BULLETS], bulletSpeed[NUM_BULLETS];
bool bulletVisible[NUM_BULLETS];

// Initialize boxes and bullets
void InitializeObjects() {
    for (int i = 0; i < NUM_BOXES; i++) {
        boxes[i].x = rand() % 600;
        boxes[i].y = rand() % 200; // Adjust the random range to control initial height
        boxes[i].visible = true;
    }
    for (int i = 0; i < NUM_BULLETS; i++) {
        bulletVisible[i] = false;
    }
}



// Fire a bullet
void FireBullet() {
    for (int i = 0; i < NUM_BULLETS; i++) {
        if (!bulletVisible[i]) {
            bulletX[i] = 350;
            bulletY[i] = 650;
            bulletSpeed[i] = 10;
            bulletVisible[i] = true;
            break;
        }
    }
}

void MoveBullets() {
    for (int i = 0; i < NUM_BULLETS; i++) {
        if (bulletVisible[i]) {
            bulletY[i] -= bulletSpeed[i];

            // Check for collision with any box
            for (int j = 0; j < NUM_BOXES; j++) {
                if (boxes[j].visible) {
                    if (bulletY[i] <= boxes[j].y + BOX_HEIGHT && bulletY[i] >= boxes[j].y &&
                        bulletX[i] >= boxes[j].x && bulletX[i] <= boxes[j].x + BOX_WIDTH) {

                        // Handle collision based on side
                        int collisionSide = (bulletX[i] - boxes[j].x) * 2 / BOX_WIDTH;
                        if (collisionSide == 0) {
                            // Left side collision
                            boxes[j].x = 700 - BOX_WIDTH;
                            boxes[j].y = 0;
                        }
                        else if (collisionSide == 2) {
                            // Right side collision
                            boxes[j].x = 0;
                            boxes[j].y = 0;
                        }
                        else {
                            // Center collision
                            boxes[j].visible = false;
                        }

                        // Deactivate the bullet after the first collision
                        bulletVisible[i] = false;
                        break;
                    }
                }
            }

            // Remove bullet if it goes off-screen
            if (bulletY[i] < 0) {
                bulletVisible[i] = false;
            }
        }
    }
}

// Handle bullet and box collisions
void HandleBulletBoxCollision() {
    for (int j = 0; j < NUM_BULLETS; j++) {
        if (bulletVisible[j]) {
            for (int i = 0; i < NUM_BOXES; i++) {
                if (boxes[i].visible) {
                    // Check for collision with the box
                    if (bulletY[j] <= boxes[i].y + BOX_HEIGHT && bulletY[j] >= boxes[i].y &&
                        bulletX[j] >= boxes[i].x && bulletX[j] <= boxes[i].x + BOX_WIDTH) {

                        // LEFT SIDE COLLISION
                        if (bulletX[j] >= boxes[i].x && bulletX[j] < boxes[i].x + 3) {
                            boxes[i].x = 700 - BOX_WIDTH;
                            boxes[i].y = 0;
                        }
                        // RIGHT SIDE COLLISION
                        else if (bulletX[j] >= boxes[i].x + BOX_WIDTH - 3 && bulletX[j] <= boxes[i].x + BOX_WIDTH) {
                            boxes[i].x = 0;
                            boxes[i].y = 0;
                        }
                        // CENTER COLLISION
                        else if (bulletX[j] >= boxes[i].x + BOX_WIDTH / 2 - 2 && bulletX[j] <= boxes[i].x + BOX_WIDTH / 2 + 2) {
                            boxes[i].visible = false;
                        }

                        bulletVisible[j] = false;
                        break;
                    }
                }
            }
        }
    }
}

// Animate the boxes
void AnimateBoxes() {
    while (true) {
        for (int i = 0; i < NUM_BOXES; i++) {
            if (boxes[i].visible) {
                boxes[i].y += 2;
                if (boxes[i].y > 700) {
                    boxes[i].y = 0;
                    boxes[i].x = rand() % 600;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

// Main game loop
void GameLoop(void* v) {
    InitializeObjects();
    std::thread boxThread(AnimateBoxes);

    while (true) {
        if (keypressed) {
            FireBullet();
            keypressed = false;
        }

        HandleBulletBoxCollision();
        MoveBullets();

        FillRect(panel, 0, 0, 700, 700, 0);

        for (int i = 0; i < NUM_BOXES; i++) {
            if (boxes[i].visible) {
                FillRect(panel, boxes[i].x, boxes[i].y, BOX_WIDTH, BOX_HEIGHT, 0xff0000);
            }
        }

        for (int i = 0; i < NUM_BULLETS; i++) {
            if (bulletVisible[i]) {
                FillRect(panel, bulletX[i], bulletY[i], 5, 5, 0x00ff00);
            }
        }

        DisplayImage(FRM1, panel);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    boxThread.join();
}

// GUI creation function
void ICGUI_Create() {
    ICG_MWTitle("Falling Boxes Simulation");
    ICG_MWSize(700, 700);
    ICG_SetFont(30, 12, "");
}

// Keyboard event handler (spacebar detection)
void KlavyeyeBasinca(int k) {
    if (k == VK_SPACE) {
        keypressed = true;
    }
}

// Main GUI components
void ICGUI_main() {
    CreateImage(panel, 700, 700, ICB_UINT);
    FRM1 = ICG_FrameMedium(5, 5, 700, 700);
    FillRect(panel, 0, 0, 700, 700, 0);
    DisplayImage(FRM1, panel);
    BTN = ICG_TButton(575, 5, 100, 50, "START", GameLoop, NULL);
    ICG_SetOnKeyPressed(KlavyeyeBasinca);
}