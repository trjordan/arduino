int state; // Current PWM state, 0 - PWM_RANGE
int band; // Boundary for PWM state.
int PWM_RANGE = 20; // Number of cycles to PWM over
int outer_state; // Unused

void setup() {
    int i;
    for (i = 2; i < 12; i++) {
        pinMode(i, OUTPUT);
    }
    state = 0;
    outer_state = 0;
}

void set_bank(int high) {
   int i;
   for (i = 2; i < 12; i++) {
        if (high) {
            digitalWrite(i, HIGH);   // set the LED on
        } else {
            digitalWrite(i, LOW);   // set the LED on
        }
    }
}

void run_dimmer() {
    if (state < band) {
        set_bank(1);
    } else {
        set_bank(0);
    }
    state++;
    if (state > PWM_RANGE) {
        state = 0;
    }
}

void loop() {
    unsigned long cur_time = millis() % 2000;
    if (cur_time < 1000) {
        band = cur_time / 100;
    } else {
        band = 20 - cur_time / 100;
    }

    band += 2;

    run_dimmer();
}
