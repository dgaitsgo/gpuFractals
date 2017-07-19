WebGL demos:

Volume Rendering
Physical-Based Rendering
Noise
Connectome

![Screen shot](https://github.com/dgaitsgo/gpuFractals/blob/master/images/ss.png)

Fractals are magnificent self-similar patterns who reveal the inner dimensions of 1-dimensional shapes.
Here we render them on the GPU for speed and precision to explore patterns those patterns to deeper depths.

#### Compatability

This has been tested on OS X 10.9.5 to 10.10.5.

You'll need to install [SDL2](https://www.libsdl.org/download-2.0.php)

#### Launch codes

```
$>make
$>./fractal [mandelbrot][newton][julia]
```

#### Let's explore

As you can see above, you can render three different fractal patterns: ```mandelbrot```,
```newton``` and ```julia```. Zoom all the way out on ```newton```. It's wild.

##### Zoom

<kbd>&plus;</kbd> - zoom in

<kbd>&minus;</kbd> - zoom out

##### Move around

<kbd>&uparrow;</kbd>
<kbd>&leftarrow;</kbd>
<kbd>&rightarrow;</kbd>
<kbd>&downarrow;</kbd>


#### Increase precision

Not all macs between 2013 and now support ```double``` precision in OpenCL kernels. It's worth finding out if yours does because you can go deeper into the fractals with more details.

```
$> sh adjustPrecision.sh double
```

If it doesn't work, switch back:
```
$> sh adjustPrecision.sh float
```
