# SAeimages
useful image editing and bitmap file manipulation functions

code written using [MAJERLE's code style](https://github.com/MaJerle/c-code-style)

  <img src="https://github.com/ckizp/SAeimages/blob/main/web/img/SAeimages.png?raw=true" width=50%>


### Image processing offered by our program :

- 1 - Grayscale
- 2 - Invert colors
- 3 - Monochromatic
- 4 - Contour extraction
- 5 - Overlay

## Usage

### Requirements
- GCC Compiler (C/C++ Compiler) and 'make' utility (both included in the MinGW and Cygwin packages for Windows)
- Python 3.x interpreter and runtime or a software (IDE like Spyder) to run python scripts

#### From a website

First download or clone this repository.
Open Command Prompt or Windows Powershell inside the `src` directory or use `cd` to navigate and use `make` to generate an executable.
```sh
make all
make clean
```

Move the executable to the `web` directory. Then run the file `lancer_interface.py` from an IDE (Ex: Spyder) or with the following command :
```sh
python lancer_interface.py
```

#### From CMD
* Syntax
  ```sh
  «path to SAeimages.exe» «path to the directory of your images» «1-5 : choose the desired processing» «first file name» «second file name (only if you choose overlay processing)»
  ```
* Example : Image to grayscale & Overlay
  ```sh
  SAeimages.exe ../../ 1 test1.bmp
  SAeimages.exe ../../ 5 test1.bmp test2.bmp 
  ```
  
## Screenshots

### 01. Website

  <img src="https://github.com/ckizp/SAeimages/blob/main/web/img/website.png" width=50%>

### 02. Console

  <img src="https://github.com/ckizp/SAeimages/blob/main/web/img/console.png" width=50%>

### 03. Examples

- BMP files :

  <img src="https://github.com/ckizp/SAeimages/blob/main/web/img/test2.png" width=180px><img src="https://github.com/ckizp/SAeimages/blob/main/web/img/test3.png" width=180px>
  
- Processings :

  <img src="https://github.com/ckizp/SAeimages/blob/main/web/img/grayscale.png" width=180px><img src="https://github.com/ckizp/SAeimages/blob/main/web/img/invert.png" width=180px><img src="https://github.com/ckizp/SAeimages/blob/main/web/img/monochromatic.png" width=180px><img src="https://github.com/ckizp/SAeimages/blob/main/web/img/contours.png" width=180px><img src="https://github.com/ckizp/SAeimages/blob/main/web/img/overlay.png" width=180px>
  
## Contact
Ibraguim - ibav9506@gmail.com

Project Link : [https://github.com/ckizp/SAeimages](https://github.com/ckizp/SAeimages)
