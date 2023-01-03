# TU-Vienna-EfficientPrograms

Assignment for lecture efficient programs WS22

## Installation and Setup

### Cmake installation on TU server

1. Download cmake installation [script](https://cmake.org/download/) with wget: 
```console
wget https://github.com/Kitware/CMake/releases/download/v3.25.1/cmake-3.25.1-linux-x86_64.sh
```
2. Run the bash script:
```console
bash cmake-3.25.1-linux-x86_64.sh
```
3. Create a .profile file in your $HOME directory:
```console
touch. profile

```
4. Add the following line to the **.profile** file:
```console
export PATH="$PATH:$HOME/cmake-3.25.1-linux-x86_64/bin/"
```
5. Add the following line to your **.bash_profile** located in your **$HOME** directory.
```console
source $HOME/.profile
```
6. Logout of your current session. After loggin in, check if cmake is installed properly by running:
```console
cmake --version
```