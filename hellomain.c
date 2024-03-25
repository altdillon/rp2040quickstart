#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() 
{
    bool inv = true;
    // const uint gpio_out = 2;
    // const uint gpio_out2 = 3;
    // gpio_init(gpio_out);
    // gpio_init(gpio_out2);
    // gpio_set_dir(gpio_out, GPIO_OUT);
    // gpio_pull_down(gpio_out);
    // gpio_set_dir(gpio_out2, GPIO_OUT);
    // gpio_pull_down(gpio_out2);
    const uint pin_in = 2;
    const uint pin_pwm = 27;
    // setup gpio for pwm
    gpio_set_function(pin_pwm,GPIO_FUNC_PWM);
    // find the pwm slice that the pin is on
    uint slice_num = pwm_gpio_to_slice_num(pin_pwm);
    // set period
    pwm_set_wrap(slice_num,16);
    pwm_set_chan_level(slice_num,PWM_CHAN_A,8);
    pwm_set_chan_level(slice_num,PWM_CHAN_B,8);
    pwm_set_enabled(slice_num,true);

    gpio_init(pin_in);
    gpio_set_dir(pin_in,GPIO_IN);
    gpio_pull_down(pin_in);

    for(uint32_t gpio = 6;gpio < 20;gpio++)
    {
        gpio_init(gpio);
        gpio_set_dir(gpio,GPIO_OUT);
    }

    const uint bits = 8;
    const uint gpio_start = 6; 
    uint counter = 0; 
    while(true)
    {
        for(uint i=0;i<bits;i++)
        {
            uint mask = 0x01;
            uint pin = gpio_start + i;
            if((counter & (mask << i)) > 0)
            {
                gpio_put(pin,1);
            }
            else
            {
                gpio_put(pin,0);
            }
        }
        counter = (counter + 1) % 256;
        sleep_ms(100);

        // counter = (counter + 1) % bits;
        // sleep_ms(300);
        // gpio_put(gpio_out,1);
        // gpio_put(gpio_out2,0);
        // sleep_ms(250);
        // gpio_put(gpio_out,0);
        // gpio_put(gpio_out2,1);
        // sleep_ms(250);
        // for(uint32_t gpio = 6;gpio < 28;gpio++)
        // {
        //     if(inv == false)
        //     {
        //         gpio_put(gpio,1);
        //         sleep_ms(80);
        //         gpio_put(gpio,0);
        //         sleep_ms(80);
        //     }
        //     else
        //     {
        //         gpio_put(gpio,0);
        //         sleep_ms(80);
        //         gpio_put(gpio,1);
        //         sleep_ms(80);
        //     }
        // }
        // inv = !inv; 
    }

    //setup_default_uart();
    //printf("Hello, world!\n");
    return 0;
}