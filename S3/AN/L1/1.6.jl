function w(x)
n = parse(Int,x,base=2)
reinterpret(Float64,n)
end