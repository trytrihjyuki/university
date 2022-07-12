gracze = ['Jula', 'Maciek', 'Kacper', 'Maurycy', 'Mikołaj']
punkty = {g: 0 for g in gracze}
przelicznik = {i+1: 5-i for i in range(5)}
rundy = ['las', 'piaski', 'lód']

for r in rundy:
    print(f'\n\nPodaj miejsca z {r} dla poszczególnych graczy:\n\n')
    for g in gracze:
        print(f'Podaj miejsce gracza: {g}')
        miejsce = int(input())
        print(miejsce)
        punkty[g] += przelicznik[miejsce]
        print('\n\n')


print('Oto Punktacja końcowa:\n\n')
print(sorted(punkty.items(), key=lambda item: item[1]),'\n')