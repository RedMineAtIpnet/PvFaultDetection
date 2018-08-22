
figure(1) 
plot(tension,puissance,'g');
ylim([0 300])
xlim([0 37])
title('La variation des caract�ristiques de P-V en fonction de la variation de la temp�rature');
xlabel('tension');
ylabel('puissance');
figure(2)
plot(tension,courant);
ylim([0 12])
xlim([0 37])
title('La variation des caract�ristiques de I-V en fonction de la variation de la temp�rature');
xlabel('tension');
ylabel('intensit�');
posmax=1;
for i=1:1001
    if puissance(i)==max(puissance)
        posmax=i;
    end
end
courant(posmax)
tension(posmax)