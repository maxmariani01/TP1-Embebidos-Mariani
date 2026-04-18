# Falla C — Margen de stack insuficiente

**Intervención:** en `linker.ld`, `__reset_stack_pointer = ORIGIN(RAM) + 16` en vez de `+ LENGTH(RAM)`.

**Síntoma esperado:** LED queda fijo encendido. El primer push del prólogo de `main()` sobreescribe `.bss` y `.data`.

**Reproducir:**
```bash
cp fallas/falla_C/linker.ld proyecto/linker.ld
cd proyecto && make clean && make && sudo make flash
```

Evidencia completa en `evidencia/falla_C/`.
