#!/bin/bash

# Aggiunge tutti i file modificati e nuovi
git add *

# Chiede all'utente di inserire un messaggio per il commit
echo "Enter the commit message: "
read commit_message

# Esegue il commit con il messaggio inserito
git commit -m "$commit_message"

# Conferma prima di eseguire il push
echo "Are you sure you want to push to 'origin master'? (y/n)"
read confirmation

if [ "$confirmation" = "y" ]; then
    # Esegue il push su origin master
    git push origin master
else
    echo "Push canceled."
fi