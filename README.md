# imgui-vulkan-template
imgui vulkan Template for simple GUIs

## Cloning the repo
Because of the submodules, this repo needs to be cloned using:
```
git clone --recursive git@github.com:TobiDeBoumaa/imgui-vulkan-template.git
```
## Build
Build the project using cmake with the following command:
```
cmake -S . -Bbuild -D CMAKE_BUILD_TYPE=Release
```
```
cmake --build build --config Release
```

> [!WARNING]  
> When building without Visual Studio (not on Windows) remove the --config option

<details>
<summary>Building Debug version</summary>
```
cmake -S . -Bbuild -D CMAKE_BUILD_TYPE=Debug
```
```
cmake --build build --config Debug
```
</details>

## Requirements
<details>
<summary>Requirements Windows</summary>
vulkan sdk is required: https://vulkan.lunarg.com/sdk/home#windows
</details>


<details>
<summary>Requirements Ubuntu Linux</summary>
```
apt install vulkan-tools
apt install libwayland-dev pkg-config libxkbcommon-dev libx11-dev libxrandr-dev libxinerama-dev libxi-dev
```
vulkan sdk 'can' also be necessary: https://vulkan.lunarg.com/doc/sdk/1.3.239.0/linux/getting_started_ubuntu.html

</details>





<details>
<summary>Requirements Arch Linux</summary>
  
```
pacman -S vulkan-tools
pacman -S wayland
pacman -S libxkbcommon libxrandr libxinerama libxi
```

</details>
