#!/usr/bin/python
# -*- coding: utf-8 -*-

#pip install pyqrcode
#pip install pypng

import pyqrcode


data = pyqrcode.create("Le football /futbol/ (dans la langue orale, par apocope, le foot), ou soccer (en Amérique du Nord), est un sport collectif qui se joue principalement au pied avec un ballon sphérique. Il oppose deux équipes de onze joueurs dans un stade, que ce soit sur un terrain gazonné ou sur un plancher. L'objectif de chaque camp est de mettre le ballon dans le but adverse, sans utiliser les bras, et de le faire plus souvent que l'autre équipe. Codifié par les écossais Britanniques2, à la fin du xixe siècle, le football s'est doté en 1904 d'une fédération internationale, la FIFA. Pratiqué en 2006 par environ 264 millions de joueurs à travers le monde, le football possède le statut de sport numéro un dans la majorité des pays. Certains continents, comme l'Afrique, l'Amérique du Sud et l'Europe, sont même presque entièrement dominés par cette discipline. La simplicité du jeu et le peu de moyens nécessaires à sa pratique expliquent en partie ce succès. Le calendrier est dominé")
data.svg('uca-url.svg', scale=8)
data.png('code.png', scale=6, module_color=[0, 0, 0, 128], background=[0xff, 0xff, 0xcc])
