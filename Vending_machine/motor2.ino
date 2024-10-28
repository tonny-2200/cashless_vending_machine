// function for motor 2 movement
void motor2()
{
    pinMode(motor1PWM, OUTPUT);
    pinMode(motor1Dir, OUTPUT);
    pinMode(motor2PWM, OUTPUT);
    pinMode(motor2Dir, OUTPUT);
    
    uint16_t ID = tft.readID();
    
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    buttons();



    while (true){
    bool down = Touch_getXY();
    on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
    off_btn.press(down && off_btn.contains(pixel_x, pixel_y));

    if (on_btn.justReleased()) {
        on_btn.drawButton();
    } else if (off_btn.justReleased()) {
        off_btn.drawButton();
    }

    if (on_btn.justPressed()) {
        on_btn.drawButton(true);
        while (counter < 2) {
            // Rotate Motor 1 (Anticlockwise)
            digitalWrite(motor1Dir, LOW);  // Set to LOW for anticlockwise
            analogWrite(motor1PWM, motorSpeed);

            // Delay for one rotation
            delay(rotationDelay);

            // Stop Motor 1
            analogWrite(motor1PWM, 0);

            // Optional: Add further actions or delays as needed
            delay(1000);

            // Rotate Motor 1 (clockwise)
            digitalWrite(motor1Dir, HIGH);  // Set to HIGH for clockwise
            analogWrite(motor1PWM, motorSpeed);

            // Delay for one rotation
            delay(rotationDelay);

            // Stop Motor 1
            analogWrite(motor1PWM, 0);

            // Optional: Add further actions or delays as needed
            delay(1000);

            counter++;
            
            
        }
        gk();
        resetArduino();        
    } else if (off_btn.justPressed()) {
        off_btn.drawButton(true);
        while (count < 2) {
            // Rotate Motor 2 (Anticlockwise)
            digitalWrite(motor2Dir, HIGH);  // Set to LOW for anticlockwise
            analogWrite(motor2PWM, motorSpeed);

            // Delay for one rotation
            delay(rotationDelay);

            // Stop Motor 2
            analogWrite(motor2PWM, 0);

            // Optional: Add further actions or delays as needed
            delay(1000);

            // Rotate Motor 2 (clockwise)
            digitalWrite(motor2Dir, LOW);  // Set to HIGH for clockwise
            analogWrite(motor2PWM, motorSpeed);

            // Delay for one rotation
            delay(rotationDelay);

            // Stop Motor 2
            analogWrite(motor2PWM, 0);

            // Optional: Add further actions or delays as needed
            delay(1000);

            count++;
                  
        }
        gk();
        resetArduino();        
    }
}
}
