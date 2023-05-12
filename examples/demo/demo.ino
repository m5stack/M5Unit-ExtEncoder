#include <M5Stack.h>
#include <M5GFX.h>
#include "UNIT_EXT_ENCODER.h"

M5GFX display;
M5Canvas canvas(&display);
UNIT_EXT_ENCODER encoder;

char buffer[20];
uint32_t pulse    = 0;
uint8_t zero_mode = 0;

void setup() {
    M5.begin(true, false, true);
    M5.Power.begin();
    display.begin();

    canvas.setColorDepth(8);  // mono color
    canvas.setFont(&fonts::efontCN_12);
    canvas.createSprite(display.width(), display.height());
    canvas.clear(WHITE);
    canvas.setTextSize(2);
    canvas.setTextColor(BLACK);
    canvas.setCursor(0, 80);
    while (!(encoder.begin(&Wire, UNIT_EXT_ENCODER_ADDR, 21, 22, 100000UL))) {
        canvas.clear(BLACK);
        canvas.setTextColor(WHITE);
        canvas.setCursor(10, 0);
        canvas.println("No Module!");
        canvas.pushSprite(0, 0);
    }
    canvas.pushSprite(0, 0);
}

void loop() {
    M5.update();
    if (M5.BtnA.wasPressed()) {
        encoder.setZeroPulseValue(0);
    }
    if (M5.BtnB.wasPressed()) {
        encoder.resetEncoder();
    }
    if (M5.BtnC.wasPressed()) {
        zero_mode++;
        if (zero_mode > 2) zero_mode = 0;
        encoder.setZeroMode(zero_mode);
    }
    canvas.clear(BLACK);
    canvas.setCursor(20, 0);
    canvas.setTextSize(2);
    canvas.setTextColor(YELLOW);
    canvas.printf("U161 EXT ENCODER 测试");
    canvas.setColor(ORANGE);
    canvas.drawLine(0, 25, 320, 25);
    canvas.setTextSize(2);
    canvas.setTextColor(WHITE);
    canvas.setCursor(0, 30);
    canvas.printf("编码器:");
    canvas.setCursor(95, 30);
    canvas.setTextColor(GREEN);
    canvas.printf("%d", encoder.getEncoderValue());
    canvas.setCursor(0, 90);
    canvas.setTextColor(WHITE);
    canvas.printf("毫米值:");
    canvas.setCursor(95, 90);
    canvas.setTextColor(GREEN);
    canvas.printf("%d mm", encoder.getMeterValue());
    canvas.setCursor(0, 60);
    canvas.setTextColor(WHITE);
    canvas.printf("圈数:");
    canvas.setCursor(65, 60);
    canvas.setTextColor(YELLOW);
    canvas.printf("%d", encoder.getZeroPulseValue());
    canvas.setCursor(110, 150);
    canvas.setTextColor(WHITE);
    switch (zero_mode) {
        case 0:
            canvas.printf("[模式:");
            canvas.setCursor(180, 150);
            canvas.setTextColor(BLUE);
            canvas.printf("无限]");
            break;
        case 1:
            canvas.printf("[模式:");
            canvas.setCursor(180, 150);
            canvas.setTextColor(YELLOW);
            canvas.printf("上升沿清零]");
            break;
        case 2:
            canvas.printf("[模式:");
            canvas.setCursor(180, 150);
            canvas.setTextColor(GREEN);
            canvas.printf("下降沿清零]");
            break;

        default:
            break;
    }

    canvas.setTextSize(2);
    canvas.setTextColor(WHITE);
    canvas.setColor(ORANGE);
    canvas.drawLine(0, 180, 320, 180);
    canvas.setCursor(10, 180);
    canvas.printf("Z Counter");
    canvas.setTextSize(2);
    canvas.setTextColor(WHITE);
    canvas.setCursor(30, 210);
    canvas.printf("清零");
    canvas.setCursor(130, 180);
    canvas.setTextSize(2);
    canvas.setTextColor(WHITE);
    canvas.printf("编码器");
    canvas.setCursor(130, 210);
    canvas.setTextSize(2);
    canvas.setTextColor(WHITE);
    canvas.printf("清零");
    canvas.setCursor(230, 180);
    canvas.printf("Z Mode");
    canvas.setCursor(230, 210);
    canvas.printf("设置");
    canvas.pushSprite(0, 0);
}