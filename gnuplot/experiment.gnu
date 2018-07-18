set terminal svg size 600,600 dynamic enhanced fname 'Verdana, Helvetica, Arial, sans-serif' 
#set terminal png size 600,600  enhanced font 'Verdana,12' 14

# Définitions des axes
set style line 11 lc rgb 'black' lt 1
set border 3 back ls 11
set tics nomirror


# Définitions grille
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12

# Définitions du style des lignes
set style line 1 lc rgb 'black' 	pt 7 ps 1 lt 1 lw 3		# D1
set style line 2 lc rgb '#dd181f'	pt 5 ps 1 lt 1 lw 3		# Rouge
set style line 3 lc rgb '#09ad00' 	pt 13 ps 1 lt 1 lw 3 	# Verte
set style line 4 lc rgb '#0060ad'	pt 9 ps 1 lt 1 lw 3		# blue

# Définitions du texte de la légende
title_CA_LC = "Contrats low cost"
title_CA = "Contrats"


###### PLOT 1
file_source = "experiment.dat"
set output "experiment1.dat.svg"
set xlabel "xlabel" font ",20"
set ylabel "ylabel" font ",20"
set key on inside right top
#set xrange [0:1000]
#set yrange [0:1]

plot file_source using (column("X")):(column("Y")):(column("Yerror"))   title title_CA  with yerrorbars linestyle 3, \
	 file_source using (column("X")):(column("Y")) w lines ls 3 title ''
