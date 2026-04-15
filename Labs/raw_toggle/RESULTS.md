# Raw Toggle Baseline
Date: 2026-04-15 · Board: NUCLEO-F446RE · Clock: 180MHz
Measurement: DWT->CYCCNT, 1000 iterations averaged, 100 iteration warm-up

## Hypothesis
ART off ~8 cycles (~44ns). ART on ~5 cycles (~28ns).
Based on pipeline model: 5 instructions × 1 cycle at 180MHz.

## Results

| Optimization | ART state | Cycles/iter | ns/iter | Notes                          |
|-------------|-----------|-------------|---------|--------------------------------|
| -O0         | off       | 24.06       | 133.7   | loop overhead dominates        |
| -O0         | on        | 17.05       |  94.7   | cache helps loop overhead too  |
| -O1         | off       | 13.01       |  72.3   | branch flush pays flash penalty|
| -O1         | on        |  4.02       |  22.3   | cache eliminates flash penalty |
| -O2         | off       | 14.00       |  77.8   | alignment slightly worse       |
| -O2         | on        |  4.02       |  22.3   | identical to -O1.              |

Pipeline model prediction: ~5 cycles ART off, ~5 cycles ART on.
Best measured result: 4.02 cycles at -O1 ART on.

## ART benefit by optimization level
-O0: 7 cycle reduction (29%)
-O1: 9 cycle reduction (69%)
-O2: 10 cycle reduction (71%)

## What Surprised Me
I expected higher optimization to always mean faster code, but the data showed otherwise. At -O2 with ART off, performance was marginally worse than -O1 — the reason being that the compiler's aggressive optimization assumes the instruction cache is present and makes code layout decisions that are correct for cache-warm execution but backfire when ART is disabled. The compiler is not wrong — it is optimizing for the normal case, and ART off is the adversarial case. The second surprise was that ART does not save a fixed number of cycles regardless of optimization level — it saves more as optimization level increases (7 cycles at -O0, 9 at -O1, 10 at -O2). Tighter code at -O1 and -O2 means the loop fits cleanly in one cache line, the branch flush penalty becomes a larger proportion of the total cost, and the cache eliminates that penalty completely — whereas at -O0 the loop is so bloated with stack operations that even perfect caching cannot recover most of the overhead. Finally, my hypothesis predicted 5 cycles for -O1 ART on based on a hand-counted instruction model assuming one cycle per instruction — but the measured result was 4.02 cycles because the compiler generated a tighter loop than the model assumed, showing that theoretical pipeline predictions are conservative floor estimates, not exact predictions.