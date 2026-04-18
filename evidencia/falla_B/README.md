# Falla B — Inicialización de .data incorrecta

**Intervención:** en `linker.ld`, `_load_address` se fija en `0x08000000` en vez de `LOADADDR(.data)`.

**Síntoma esperado:** programa arranca, LED parpadea al ritmo base pero sin pausas largas. La variable `g_blink_count` vale `0x20005000` en vez de `3`.

**Reproducir:**
```bash
cp fallas/falla_B/linker.ld proyecto/linker.ld
cd proyecto && make clean && make && sudo make flash
```

Evidencia completa en `evidencia/falla_B/`.
