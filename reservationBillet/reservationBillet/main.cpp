//
//  main.cpp
//  reservationBillet
//
//  Created by Romaissaa on 17/10/2023.
//

#include "reservBillet.hpp"
#include <iostream>

int main() {
    GestionnaireReservations gestionnaire;

    Evenement event1("Concert", "2023-11-15", 100, 30.0);
    Evenement event2("Conférence", "2023-11-20", 50, 20.0);

    gestionnaire.ajouterEvenement(event1);
    gestionnaire.ajouterEvenement(event2);

    std::string nom, prenom, dateNaissance, email;

    std::cout << "Entrez votre nom : ";
    std::cin >> nom;

    std::cout << "Entrez votre prénom : ";
    std::cin >> prenom;

    std::cout << "Entrez votre date de naissance (AAAA-MM-JJ) : ";
    std::cin >> dateNaissance;

    std::cout << "Entrez votre email : ";
    std::cin >> email;

    Utilisateur user(nom, prenom, dateNaissance, email, 1, 500.0);
    gestionnaire.ajouterUtilisateur(user);

    std::cout << "Votre solde actuel est de " << user.solde << " $" << std::endl; // Affichage du solde initial

    std::cout << "Liste des événements avec places disponibles : " << std::endl;
    gestionnaire.afficherEvenementsAvecPlacesEtPrix();

    std::string nomEvenement;
    std::cout << "Choisissez un événement : ";
    std::cin >> nomEvenement;

    Evenement eventChoisi;
    for (const Evenement& e : gestionnaire.getEvenements()) {
        if (e.nom == nomEvenement) {
            eventChoisi = e;
            break;
        }
    }

    int nbBillets;
    std::cout << "Nombre de billets à réserver : ";
    std::cin >> nbBillets;

    Utilisateur utilisateur = gestionnaire.trouverUtilisateur(user.nom);
    gestionnaire.reserverBillets(utilisateur, eventChoisi, nbBillets);

    std::cout << "Nouveau solde : " << utilisateur.solde << " $" << std::endl;

    return 0;
}
