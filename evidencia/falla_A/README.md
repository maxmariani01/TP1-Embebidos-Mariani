# Falla A — Vector table mal ubicada

**Intervención:** en `linker.ld`, dentro de `SECTIONS`, se declara `.text` antes de `.vectors`.

**Síntoma esperado:** HardFault inmediato. LED apagado. El CPU no llega a ejecutar `Reset_Handler`.

**Reproducir:**
```bash
cp fallas/falla_A/linker.ld proyecto/linker.ld
cd proyecto && make clean && make && sudo make flash
```

Evidencia completa en `evidencia/falla_A/`.
