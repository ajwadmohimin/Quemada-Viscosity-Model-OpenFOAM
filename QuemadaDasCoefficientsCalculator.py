import math

hct = 0.45

k0 = 0.275363 + (2 / (0.100158 + hct))
kInf = math.exp(1.3435 - 2.803 * hct + 2.711*hct**2 - 0.6479*hct**3)
gammaDot = math.exp(-6.1508 + 27.923*hct - 25.60*hct**2 + 3.697*hct**3)

print("Hct  ",hct)
print("k0 ", k0)
print("kInf ", kInf)
print("gammaDot ", gammaDot)
