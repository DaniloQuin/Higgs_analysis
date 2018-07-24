

./RunTMVAClassification sanity_check 0 5000 12 2.5%  26

#echo "Termino RunTMVAClassification" |  mail -s "TMVATree Done" "daquinteros@uc.cl"

./RunTMVATree sanity_check 26

./RundiHiggs sanity_check 100

#echo "Termino RunTMVATree" |  mail -s "TMVATree Done" "daquinteros@uc.cl"
