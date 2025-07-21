# Linear-Regression-C

This project implements basic linear regression in C to find the line of best fit from coordinate data stored in a file. It reads `(x, y)` data points, calculates the linear regression coefficients `y = bx + a`, and allows the user to predict `y` for any input `x`.

## Features

- Reads coordinate data from a user-specified text file.
- Calculates regression line parameters:
  - Gradient (b)
  - Y-intercept (a)
- Prints the regression equation.
- Predicts `y` value for a user-input `x`.
- Handles variable data sizes dynamically using file input.

## Usage

Compile the program with:

```bash
gcc -o linear_regression linear_regression.c -lm
