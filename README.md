# Electronic Nose

An embedded electronic-nose system that samples a fragrance, analyzes its chemical signature with a trained ML model, and estimates its note families and accords, including how the scent evolves during dry-down.

> **Status:** Early development (Stage 1: hardware setup and data collection).

## How it works

```
gas sensors → chemical fingerprint → ML model → note families / accords → explained breakdown
```

Gas sensors respond to the whole vapor mixture coming off a perfume blotter and produce a combined electrical "fingerprint." A model trained on fingerprints from known samples learns to recognize perfumes and, later, broad scent families.

**What this device does not do:** it doesn't identify individual molecules or literal perfume notes. That requires lab equipment like GC-MS. It *estimates* scent characteristics from a pattern, and results are reported with that in mind.

## Roadmap

### Stage 1: Known-perfume classifier
Identify which of a set of known perfumes is being sampled.
- [ ] ESP32 + Bosch BME688 sensor setup
- [ ] Sealed sampling chamber with fan and clean-air purge
- [ ] Firmware: heater-profile sensor reads, CSV logging over serial
- [ ] Data collection: 5–10 perfumes + clean air, 20–30 samples each across multiple days
- [ ] Feature extraction, PCA visualization, k-NN / random forest classifier
- [ ] Evaluation on held-out days: accuracy, confusion matrix, failure analysis
- [ ] Live demo: blotter in → predicted perfume + confidence

### Stage 2: Scent families and accords
- [ ] Multi-label prediction of 3–5 broad families (e.g. citrus, floral, woody, amber, gourmand) on unseen perfumes
- [ ] Knowledge base linking families/accords to molecules commonly used to create them

### Stage 3: Dry-down and temperature
- [ ] Continuous sampling over 1–4 hours to measure dry-down curves
- [ ] Temperature-controlled sample stage (Peltier) with a fixed-temperature sensor chamber

### Hardware and embedded goals
- [ ] Firmware in C/C++ on FreeRTOS
- [ ] Custom sensor PCB with fan/Peltier drivers
- [ ] Automated chamber (purge pump, heated blotter stage)
- [ ] On-device inference with TensorFlow Lite Micro

## Applications
- Identifying unlabeled samples (decants, vintage bottles, room sprays)
- Comparing a bottle against an authentic reference fingerprint (counterfeit flagging)
- Objective batch-to-batch and reformulation comparisons
- Measured dry-down and longevity instead of user-voted ratings

## Repository layout

| Folder | Contents |
| --- | --- |
| `firmware/` | ESP32 firmware (PlatformIO) |
| `ml/` | Feature extraction, training, and evaluation scripts |
| `data/` | Collected sensor samples (CSV) |
| `hardware/` | Schematics, PCB files, chamber design |
| `docs/` | Notes, protocols, and writeups |

## Hardware (planned)
- ESP32 development board
- Bosch BME688 gas / temperature / humidity sensor
- Optional additional sensors: Sensirion SGP41, ScioSense ENS160
- Small sealed chamber, fan, blotter holder

## License
MIT. See [LICENSE](LICENSE).
