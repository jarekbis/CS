from microbit import *  

display.show(Image.ALL_CLOCKS,delay=200)  
aktualna=0  
znaki="0123456789.<"
liczba=""  

while True:  
    display.show(znaki[aktualna])  
    if pin0.is_touched(): 
        display.show(":"+liczba+">")  
    elif pin1.is_touched():
        display.clear()  
        liczh = float(liczba)
        calkowita = int(liczh)
        heks = hex(int(liczh))[2:]  
        if len(heks) <= 5:  
            display.set_pixel(4,len(heks),9)  
            ulamek = int((liczh-int(liczh))*16**(5-len(heks)))
            heks = heks + hex(ulamek)[2:]
            for i, h in enumerate(heks):  
                 for d in range(4):  
                     display.set_pixel(3 - d, i, 9 if int(h, 16) & (1<<d) else 0)
        else:  
             display.show("nadmiar")  
    elif button_a.is_pressed(): 
         if znaki[aktualna] == "<":  
             if len(liczba)>0: liczba = liczba[:-1]  
         elif liczba.count(".") == 0 or znaki[aktualna] != "." :  
                 liczba += znaki[aktualna]  
         display.show(":"+liczba+">")  
    elif button_b.is_pressed():
         aktualna = (aktualna + 1) % len(znaki)  
    sleep(150)