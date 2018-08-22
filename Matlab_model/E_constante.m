
figure(1) 
plot(tension,puissance,'g');
ylim([0 300])
xlim([0 37])
title('La variation des caractéristiques de P-V en fonction de la variation de la température');
xlabel('tension');
ylabel('puissance');
figure(2)
plot(tension,courant);
ylim([0 12])
xlim([0 37])
title('La variation des caractéristiques de I-V en fonction de la variation de la température');
xlabel('tension');
ylabel('intensité');
posmax=1;
for i=1:1001
    if puissance(i)==max(puissance)
        posmax=i;
    end
end
courant(posmax)
tension(posmax)