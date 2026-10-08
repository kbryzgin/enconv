# Encoding Converter
A simple CLI-utility written in C to convert text files to **UTF-8**.

## Supported Input Encodings
* **CP-1251**
* **KOI8-R**
* **ISO-8859-5**

## Prerequisites
* `gcc` compiler
* `make` build automation tool

## Building the Project
To compile the utility using strict compliance flags (`-Wall -Wextra -Wpedantic -std=c11`), run the following command in the root directory:
```bash
make
```

To clean the repository by removing object files and the generated executable, use:
```bash
make clean
```

## Usage
Run the program by passing the input file path, source encoding name, and target output path as CLI-arguments:
```bash
./converter <input_file> <encoding> <output_file>
```

### Execution Examples:
```bash
./converter tests/cp1251.txt CP-1251 output_cp1251.txt
./converter tests/koi8.txt KOI8-R output_koi8.txt
./converter tests/iso-8859-5.txt ISO-8859-5 output_iso.txt
```
