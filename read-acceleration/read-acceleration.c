#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "include/acceleration_sensor.h"

int main()
{
    stdio_init_all();
    printf("Iniciando...\n");

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Aguarda um pouco para estabilizar a comunicação I2C
    sleep_ms(100);

    printf("Inicializando MPU6050...\n");
    init_mpu6050();
    printf("MPU6050 inicializado!\n");
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    int16_t ax, ay, az;
    while (true)
    {
        read_acceleration(&ax, &ay, &az);
        float slope = calculate_slope(ax, ay, az);

        printf("Acelerômetro: X=%d, Y=%d, Z=%d\n", ax, ay, az);
        printf("Inclinação no eixo X: %.2f°\n", slope);
        sleep_ms(1000);
    }
}
