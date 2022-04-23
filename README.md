# arduino_gtest_sample

C++ GoogleTest sample for Arduino farmware.

## Sample Project Overview

### Scenario

```mermaid
sequenceDiagram

participant p as PC
participant a as Arduino
participant s as sensor

p ->>+ a: "get"
a ->>+ s: measurement command
s -->>- a: raw measurement data
a -->>- p: data
```

## License

MIT License

## Author

[toms74209200](<https://github.com/toms74209200>)

