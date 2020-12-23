using Plots
using LaTeXStringsX
using Statistics
using LinearAlgebra
using Printf

Float64

function integrate(f, a, b)
    M = 20 # maksymalna ilość kroków
    acc = 1e-5 # żądana dokładność
    
    Rc = Vector{Float64}(undef, M) # Wektor z obecnym rzędem macierzy R obliczonym metodą Romberga
    Rp =  Vector{Float64}(undef, M) # Wektor z poprzednim rzędem macierzy R
    h = (b-a) # krok
    Rp[1] = (f(a) + f(b))*h*0.5 # początek, trapezami

    for i = 2:M
        h = h/2
        c = 0
        ep = 2^(i-2)
        
        for j = 1:ep
            c += f(a + (2*j-1)*h)
        end
        Rc[1] = h*c + 0.5*Rp[1]
        
        for j = 2:i
            n_k = 4^(j-1)
            Rc[j] = (n_k*Rc[j-1] - Rp[j-1])/(n_k - 1) # obliczamy R_nm zgodnie z rekurencyjnym wzorem
        end
        
        if i > 2 && abs(Rp[i-1] - Rc[i]) < acc
            return Rc[i-1] # uzyskaliśmy żądaną dokładność
        end
        
        Rp, Rc = Rc, Rp # obecny wiersz staje się poprzednim
    end
    return Rp[M]
end

function dot_prod(f, g)
    function fg(x)
        return x*f(x)*g(x)
    end
    return integrate(fg, 0, 1)
end

function get_err(f, w)
    function diff(x)
        return f(x) - w(x)
    end
    return dot_prod(diff, diff)
end

function x_pow(pow) # funkcja zwaracjąca funkcję x^pow
    function f(x)
        return x^pow
    end
    return f
end

function get_poly(alphas) # funkcja zwracająca wielomian w o współczynnikach alfa
    n = size(alphas,1)
    function poly(x)
        X = [x_pow(i-1)(x) for i = 1:n]
        return dot(X,alphas)
    end
    return poly
end

function get_opt(f, n) # f
    A = zeros((n+1, n+1))
    B = zeros((n+1,1))
    C = zeros((n+1,1))
    # tworzymy macierz A z iloczynów skalarnych podstawowej bazy PI_n
    for i = 1:(n+1)
        for j = 1:(n+1)
            A[i,j] = 1 / (i+j)
        end
    end
    for i = 1:(n+1) # macierz nietrywialnych iloczynówk skalarnych
        C[i,1] = dot_prod(f,x_pow(i-1))
    end
    B = inv(A)*C # rozwiązujemy układ równań liniowych
    return get_poly(B) # zwracamy wielomian o danych współczynnikach
end

function get_ans(f, eps)
    n = 0
    W = [] # kolejne wielomiany
    errors = [] # błędy kolejnych wielomianów
    while true # iterujemy się dopóki nie znajdziemy wielomianu optymalnego
        w = get_opt(f, n)
        n += 1
        err = get_err(f, w)
        push!(W,w)
        push!(errors, err)
        if err < eps || n > 25 # znaleźliśmy wielomian optymalny, lub max kroki
            return W, errors
        end
    end
    return W, errors
end

function solve(f, f_name, file_name, eps, animation)
    W, e = get_ans(f, eps)
    if animation # kod do tworzednia animacji
        df = size(W,1)
        anim =  @animate for i = 1:df
            a = W[i].(0:0.01:1)
            b = f.(0:0.01:1)
            max = maximum([maximum(a),maximum(b)])
            min = minimum([minimum(a),minimum(b)])
            diff = max - min # wszystkie powyższe linijki są po to, żeby napisy nie skakały
            plot(0:0.01:1,[W[i],f],legend=:topleft, label = [L"w_n^*" f_name])
            err = @sprintf("%5.10f", e[i])
            annotate!(0.085, min+0.5*diff, text("n: " * string(i), :black, :right, 10))
            annotate!(0.3, min+0.45*diff, text("error: " * err, :red, :right, 10))
        end
        gif(anim, file_name * ".gif", fps = 2)
    end
    return e
end

almost_inv(x) = 1 / (x + 1e-3)
poly_3(x) = 0.5 - 2*x + 0.01*x^2 + 100*x^3
poly_4(x) = 3 + 3.5*x + x^2 - 1000*x^4
sin_inv(x) = sin(1/(x+1e-3))

functions = [sin, tan, exp, almost_inv, sqrt, poly_3, poly_4, sin_inv]
functions_names = [L"\sin", L"tg", L"e^x", L"\frac{1}{x}", L"\sqrt{x}", L"w_3", L"w_4", L"\sin{\frac{1}{x}}"]
eps = [1e-9, 1e-9, 1e-9, 1, 1e-6, 1e-9, 1e-9, 2*1e-2]
file_names = ["sin", "tg", "exp", "inv", "sqrt", "poly_3", "poly_4", "sin_inv"]

errors = []
for i in eachindex(functions)
    err = solve(functions[i], functions_names[i], file_names[i], eps[i], true)
    push!(errors, err)
end