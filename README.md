# Giraffe generator by rybka 🐟 plum

Giraffe generator made for Motorola Science Cup contest

Project was created on Linux where configuration shouldn't cause much problems.

# Usage

## Requirements
`python3` is required to run `run.py` script.
There shouldn't be a problem with `main`, but `libpng` may be required.

## Running
Use `run.py` script if you want to enter parameters manually.
You can also import the script and use a provided function to automate it.

The other way is to write directly to stdin of `main`.

## Examples
There are two types of examples:
- `*.py` - those are run with `python3 {example-file}`
- `*.txt` - those are run with `./main < {example-file}`

```
basic_input.txt
---
giraffe - name of the file
512 512 - width and height
1 - scale
0 - giraffe type (Reticulated giraffe)
0 - skip colors customization
0 - skip patches customization
```

```
colored_giraffe.txt
---
colored_giraffe.png - name of the file
512 512 - width and height
2.0 - scale
3 - giraffe type (Kordofan giraffe)
1 - customize colors
202 127 79 - patch color
232 223 202 - gap color
112 74 56 - middle color 
237 208 144 - secondary color
0 - skip patches customization
```


## Format
Generator (`main`) reads parameters from stdin in the following format:
```
{general parameters}
0 | (1 {color parameters})
0 | (1 {patch parameters})
```

## Parameter order 

Note: All parameters are in relation to 512x512 image.
Image size 'crops' and has no effect on the pattern

### General
- `filename {string}` - of result image
- `width {uint}` - of result image
- `height {uint}` - of result image
- `scale {float}` - scales *area* of texture elements
- `giraffe index {uint}` - number between 0 and 8 representing giraffe 

### Colors
- `patch {color}` - overall, average color of a patch
- `gap {color}` - space between the patches
- `middle {color}` - color deeper inside the patch, usually darker
- `secondary {color}` - adds some variation 

### Patches
Size
- `scale {float}` - scale of patch area - greater scale = bigger patches and fewer of them
- `(min and max) gap {float}` - how far apart the patches are
- `min to max area ratio {float}` - measure of how different in size the patches are
- `standard deviation {float}` - size is randomly selected with normal distribution

Edges - created by adding noise to generated patches.
Each property has 3 values: `frequency {float}`,  `strength {float}`, `octaves {uint}`
- `distortion` - controls bigger indents in the patch
- `roughness` - more local than distortion and has weaker effect

### Spikes
- `(min and max) count {uint]` - how many spikes should a patch have
- `(min and max) depth {float}` - how far into patch the spike extends
- `(min and max) width {float}` - width (thickness) of the spike

## Code
### Requirements
  - `c++20 `
  - `libpng` and `libpng-config`
  - `python3` version `3.6+`
  - optionally `Pillow` for `mosaic.py`

Running `make` build `main` program.


# Images
## Reticulated giraffe
![s0-0](images/0-0.png)
![s0-1](images/0-1.png)
![s0-2](images/0-2.png)
![s0-3](images/0-3.png)
![s0-4](images/0-4.png)

![s0-5](images/0-5.png)
![s0-6](images/0-6.png)
![s0-7](images/0-7.png)
![s0-8](images/0-8.png)
![s0-9](images/0-9.png)

## West African giraffe
![s1-0](images/1-0.png)
![s1-1](images/1-1.png)
![s1-2](images/1-2.png)
![s1-3](images/1-3.png)
![s1-4](images/1-4.png)

![s1-5](images/1-5.png)
![s1-6](images/1-6.png)
![s1-7](images/1-7.png)
![s1-8](images/1-8.png)
![s1-9](images/1-9.png)

## Nubian giraffe
![s2-0](images/2-0.png)
![s2-1](images/2-1.png)
![s2-2](images/2-2.png)
![s2-3](images/2-3.png)
![s2-4](images/2-4.png)

![s2-5](images/2-5.png)
![s2-6](images/2-6.png)
![s2-7](images/2-7.png)
![s2-8](images/2-8.png)
![s2-9](images/2-9.png)

## Kordofan giraffe
![s3-0](images/3-0.png)
![s3-1](images/3-1.png)
![s3-2](images/3-2.png)
![s3-3](images/3-3.png)
![s3-4](images/3-4.png)

![s3-5](images/3-5.png)
![s3-6](images/3-6.png)
![s3-7](images/3-7.png)
![s3-8](images/3-8.png)
![s3-9](images/3-9.png)

## Angolan giraffe
![s4-0](images/4-0.png)
![s4-1](images/4-1.png)
![s4-2](images/4-2.png)
![s4-3](images/4-3.png)
![s4-4](images/4-4.png)

![s4-5](images/4-5.png)
![s4-6](images/4-6.png)
![s4-7](images/4-7.png)
![s4-8](images/4-8.png)
![s4-9](images/4-9.png)

## South African giraffe
![s5-0](images/5-0.png)
![s5-1](images/5-1.png)
![s5-2](images/5-2.png)
![s5-3](images/5-3.png)
![s5-4](images/5-4.png)

![s5-5](images/5-5.png)
![s5-6](images/5-6.png)
![s5-7](images/5-7.png)
![s5-8](images/5-8.png)
![s5-9](images/5-9.png)
## Rothschild giraffe
![s6-0](images/6-0.png)
![s6-1](images/6-1.png)
![s6-2](images/6-2.png)
![s6-3](images/6-3.png)
![s6-4](images/6-4.png)

![s6-5](images/6-5.png)
![s6-6](images/6-6.png)
![s6-7](images/6-7.png)
![s6-8](images/6-8.png)
![s6-9](images/6-9.png)

## Thornicroft giraffe
![s7-0](images/7-0.png)
![s7-1](images/7-1.png)
![s7-2](images/7-2.png)
![s7-3](images/7-3.png)
![s7-4](images/7-4.png)

![s7-5](images/7-5.png)
![s7-6](images/7-6.png)
![s7-7](images/7-7.png)
![s7-8](images/7-8.png)
![s7-9](images/7-9.png)

## Masai giraffe
![s8-0](images/8-0.png)
![s8-1](images/8-1.png)
![s8-2](images/8-2.png)
![s8-3](images/8-3.png)
![s8-4](images/8-4.png)

![s8-5](images/8-5.png)
![s8-6](images/8-6.png)
![s8-7](images/8-7.png)
![s8-8](images/8-8.png)
![s8-9](images/8-9.png)


## Mosaic
![m](images/mosaic.png)

## Elemental giraffes

![blue-giraffe](images/elemental/water_giraffe.png)
![green-giraffe](images/elemental/earth_giraffe.png)

![fire-giraffe](images/elemental/fire_giraffe.png)
![air-giraffe](images/elemental/air_giraffe.png)

## Custom
![custom-giraffe1](images/custom_giraffe1.png)
![custom-giraffe2](images/custom_giraffe2.png)