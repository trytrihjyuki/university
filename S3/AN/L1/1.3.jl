function w(x)
x^3 - 6*x^2 + 3*x - 0.149
end

function w2(x)
((x-6)*x +3)*x - 0.149
end

function blad(x)
(abs(x+14.636489) / 14.636489)
end

print("\n\nBledy dla w(x):\n ")
print("Float16\n")
print(blad(w(Float16(4.71))))

print("\n\nFloat32\n")
print(blad(w(Float32(4.71))))

print("\n\nFloat64\n")
print(blad(w(Float64(4.71))))

print("\n\nBledy dla w2(x):")
print("\n\nFloat16\n")
print(blad(w2(Float16(4.71))))

print("\n\nFloat32\n")
print(blad(w2(Float32(4.71))))

print("\n\nFloat64\n")
print(blad(w2(Float64(4.71))))