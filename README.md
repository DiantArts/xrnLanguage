# xrnLanguage
[![Continous Integration](https://github.com/DiantArts/xrnLanguage/actions/workflows/continuous-integration.yml/badge.svg)](https://github.com/DiantArts/xrnLanguage/actions/workflows/continuous-integration.yml)

This project is a programming language inspired from C, C++, Carbon and Haskell

Here is an example of the syntax so far:
```
import Math;

class Circle {
    r: F32;
}

printTotalArea(circles: View<Circle>) {
    area: F32 = 0;
    for c in circles {
        area += Math.pi * Math.square(c.r);
    }
    print("Total area
            {}", #* arg
            number 1 *# area); # fmt syntax
}

main(argv) {
    circles: Vector<Circle> =
        (.r = 1'0.0F32),
        (.r = 20.0'F32);
    printTotalArea(circles);
    return 0;
}
```
