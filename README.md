# TP1 — Startup, linker y arranque real en STM32F103

**Sistemas Embebidos — Ingeniería Electrónica**

- **Alumno:** Máximo Daniel Mariani
- **Legajo:** 1151848
- **Docente:** Dr. Ing. Leonardo J. Amet
- **Fecha de entrega:** 22 de abril de 2026

## Resumen

Este TP analiza el arranque bare-metal de una Blue Pill (STM32F103C8T6), identificando el rol del linker script y el código de startup, y demostrando mediante tres fallas inducidas cómo se rompe el contrato entre hardware, linker y código de arranque.

Proyecto base: [LeonardoAmet/bluepill-baremetal](https://github.com/LeonardoAmet/bluepill-baremetal)

## Estructura del repositorio

| Carpeta | Contenido |
|---|---|
| `informe/` | Informe técnico en PDF y Word. |
| `proyecto/` | Versión sana del proyecto, lista para compilar. |
| `fallas/` | Versiones del `linker.ld` con cada falla inducida, con README explicativo por falla. |
| `evidencia/` | Salidas de comandos, logs de OpenOCD, diffs, observaciones de placa para cada estado. |

## Cómo reproducir

### Versión sana
```bash
cd proyecto
make clean && make
sudo make flash
```
El LED de PC13 debe parpadear 3 veces, hacer una pausa larga, y repetir.

### Cualquier falla
```bash
cp evidencia/falla_A/linker.ld proyecto/linker.ld    # o falla_B, falla_C
cd proyecto && make clean && make
sudo make flash
```
Ver el síntoma esperado en el README de cada falla y en `evidencia/falla_X/`.

### Restaurar la versión sana
```bash
git checkout proyecto/linker.ld
```

## Herramientas usadas

- `arm-none-eabi-gcc` (toolchain ARM bare-metal)
- `OpenOCD` (flasheo y debug)
- ST-Link V2 (programador)
- Blue Pill (clon CKS32/CS32, CPUTAPID `0x2ba01477`)
- WSL2 sobre Windows, VSCode
