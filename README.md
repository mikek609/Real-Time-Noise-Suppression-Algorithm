# Real-Time Noise Suppression Algorithm

## Dataset
This project uses the [Microsoft Scalable Noisy Speech Dataset (MS-SNSD)](https://github.com/microsoft/MS-SNSD).

## Getting Started (Windows)
 
### 1. Prerequisites 
Install the following tools before cloning the repo:
- **Git** — https://git-scm.com/downloads
- **Daisy Toolchain** — https://daisy.audio/toolchain-windows/

### 2. Clone the Repository
Clone the repo with all submodules in one command:
```bash
git clone --recurse-submodules https://github.com/your-username/Active-Noise-Control-ANC-Algorithm.git
```

If you already cloned without `--recurse-submodules`, run this to pull down the submodule contents:
```bash
git submodule update --init --recursive
```
 
### 3. Build the Libraries
You only need to do this **once** after cloning (or again if you update the submodules):
```bash
cd Active-Noise-Control-ANC-Algorithm/daisy_prog/libDaisy
make
cd ../DaisySP
make
cd ../..
```
 
### 4. Build the Project
From the `daisy_prog/` folder: 
```bash
cd Active-Noise-Control-ANC-Algorithm/daisy_prog
make
```
 
### 5. Flash to the Daisy Seed
1. Put the Daisy Seed into bootloader mode:
   - Hold the **BOOT** button
   - Tap the **RESET** button
   - Release the **BOOT** button 
2. Flash the binary:
   ```bash
   make program-dfu
   ``` 
   - Every time you make changes to your code, recompile and flash with:
   ```bash
   make && make program-dfu
   ```
   (Run this from the `daisy_prog/` folder)
 
## Updating Submodules
 
To pull the latest changes for `libDaisy` and `DaisySP`:
```bash
git submodule update --remote
```
 
Then rebuild the libraries:
 
```bash
cd daisy_prog/libDaisy
make
cd ../DaisySP
make
cd ../..
```
