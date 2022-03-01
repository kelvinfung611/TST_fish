This is the V1 of the kill switch test

images :
https://github.com/kelvinfung611/TST_fish/blob/main/res/kill-switch-test_images/V1%20(27%20FEB%202022)/README.md

*************************************
Tidy version is same as the original V1 code but just some commented parts removed
*************************************


Result is fine but some can be improved:

- if Serial2 keep reading garbage value, it should also be killed after 5 seconds
  a test if-statement is added but not sure if it is bug-free

- the kill should be made after 5 seconds of not reading effective command, but it sometime takes more than 5 seconds, and it kills immediately if the wire is not connected at all
