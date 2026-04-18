#include <stdint.h>

// Definición de registros y direcciones de periféricos
#define RCC_APB2ENR     (*((volatile uint32_t*)0x40021018U))
#define GPIOC_BASE      (0x40011000U)
#define GPIOC_CRH       (*((volatile uint32_t*)(GPIOC_BASE + 0x4U)))
#define GPIOC_ODR       (*((volatile uint32_t*)(GPIOC_BASE + 0xCU)))

// --- Variables testigo para el TP ---
// g_blink_count vive en .data: valor inicial = 3. Se copia de Flash a RAM.
// Si la copia de .data falla, esta variable arranca con basura y el blink se rompe.
volatile uint32_t g_blink_count = 3;

// g_zero_marker vive en .bss: debe arrancar en 0 (lo pone a cero el Reset_Handler).
// Si .bss no se limpia, tiene basura y el if nunca se cumple.
volatile uint32_t g_zero_marker;
// ------------------------------------

int main(void)
{
    // Habilitar el clock del GPIOC
    RCC_APB2ENR |= (1U << 4);

    // Configurar PC13 como salida push-pull 50 MHz
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    while (1)
    {
        // Si .bss se limpió bien, g_zero_marker == 0 y hacemos el patrón esperado:
        // parpadea g_blink_count veces y espera largo.
        if (g_zero_marker == 0)
        {
            for (uint32_t k = 0; k < g_blink_count; k++)
            {
                GPIOC_ODR &= ~(1U << 13);           // LED ON
                for (volatile int i = 0; i < 200000; i++);
                GPIOC_ODR |=  (1U << 13);           // LED OFF
                for (volatile int i = 0; i < 200000; i++);
            }
            // Pausa larga entre series
            for (volatile int i = 0; i < 1500000; i++);
        }
        else
        {
            // Si .bss no se limpió, caemos acá: LED fijo encendido (síntoma).
            GPIOC_ODR &= ~(1U << 13);
        }
    }
}