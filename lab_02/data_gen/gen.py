from random import randint

theaters = ["Big theater", "La Scala", "The grand opera", "Vienna Opera", "Covent Garden", "Metropolitan Opera",
            "Broadway theater", "Sydney Opera", "Arena di Verona", "Theater Colon", "Paris Opera", "Esplanade Theater",
            "Globus theatre", "Albert Hall"]
shows = ["Crazy money", "Wolves and Sheep", "Eugene Onegin", "Muller machine", "The Marriage of Figaro",
         "Talents and fans",
         "Hamlet collage", "A kind man from Cezuan", "Gull", "Warsaw melody", "Uncle Ivan", "Imaginary sick",
         "A dream in a summer night", "Dangerous ties", "Chess", "Pygmalion", "King Oedipus", "Opera of the Beggars",
         "Eldest son", "North wind"]
directors = ["Zhenovach", "Vyrypaev", "Grigoryan", "Serebrennikov", "Ginkas", "Tuminas", "Krymov", "Kamenkovich",
             "Karbauskis", "Gatsalov", "Vytoptov", "Bogomolov", "Klimenko", "Mundrutso", "Nyakrosius", "Barghetto",
             "Ross", "Lassalle", "Wilson", "Munavwara", "Erwin"]
composers = ["Beethoven", "Bach", "Mozart", "Wagner", "Tchaikovsky", "Verdi", "Stravinsky", "Strauss", "Rachmaninov",
             "Schubert", "Zimmer", "Goransson"]
country = ["Russia", "USA", "Italy", "Spain", "Germany", "Canada", "Australia", "Austria", "Netherlands",
          "France"]
n = 1000
f = open("../data.txt", "w")
for i in range(n):
    tmp = randint(0, 13)
    f.write(theaters[tmp]+'\n')
    tmp = randint(0, 19)
    f.write(shows[tmp]+'\n')
    tmp = randint(0, 20)
    f.write(directors[tmp]+'\n')
    mn = randint(1000, 10000)
    f.write(str(mn)+'\n')
    mx = randint(mn+500, 15000)
    f.write(str(mx)+'\n')
    c = randint(1, 3)
    f.write(str(c)+'\n')
    if c == 1:
        tmp = randint(1, 18)
        f.write(str(tmp)+'\n')
        tmp = randint(1, 2)
        f.write(str(tmp)+'\n')
    elif c == 2:
        tmp = randint(1, 3)
        f.write(str(tmp)+'\n')
    elif c == 3:
        tmp = randint(0, 11)
        f.write(composers[tmp]+'\n')
        tmp = randint(0, 9)
        f.write(country[tmp]+'\n')
        tmp = randint(1, 18)
        f.write(str(tmp)+'\n')
        tmp = randint(60, 240)
        f.write(str(tmp)+'\n')
    else:
        print("Wrong")


