//
//  reservBillet.cpp
//  reservationBillet
//
//  Created by Romaissaa on 17/10/2023.
//

#include "reservBillet.hpp"

void GestionnaireReservations::ajouterEvenement(Evenement e) {
    evenements.push_back(e);
}

void GestionnaireReservations::ajouterUtilisateur(Utilisateur u) {
    utilisateurs.push_back(u);
}

void GestionnaireReservations::reserverBillets(Utilisateur& u, Evenement e, int nbBillets) {
    for (Billet& billet : billets) {
        if (billet.nomEvenement == e.nom && billet.numeroUtilisateur == u.numero) {
            std::cout << "L'utilisateur a déjà réservé des billets pour cet événement." << std::endl;
            return;
        }
    }

    for (Evenement& ev : evenements) {
        if (ev.nom == e.nom && ev.date == e.date) {
            float prixUnitaire = ev.prix;
            float prixTotal = nbBillets * prixUnitaire;

            if (u.solde >= prixTotal) {
                ev.placesDisponibles -= nbBillets;
                u.solde -= prixTotal;
                int numeroBillet = billets.size() + 1;
                Billet billet(numeroBillet, e.nom, nbBillets, prixTotal, u.numero);
                billets.push_back(billet);
                std::cout << "Billets réservés avec succès !" << std::endl;
                return;
            } else {
                std::cout << "Solde insuffisant pour réserver les billets." << std::endl;
                return;
            }
        }
    }

    std::cout << "L'événement spécifié n'a pas été trouvé." << std::endl;
}

void GestionnaireReservations::afficherEvenementsAvecPlacesEtPrix() {
    for (const Evenement& e : evenements) {
        std::cout << "Nom : " << e.nom << ", Date : " << e.date << ", Places disponibles : " << e.placesDisponibles << ", Prix : " << e.prix << " $" << std::endl;
    }
}


void GestionnaireReservations::afficherBilletsUtilisateur(Utilisateur u) {
    for (const Billet& b : billets) {
        if (b.numeroUtilisateur == u.numero) {
            std::cout << "Numéro : " << b.numero << ", Nom de l'événement : " << b.nomEvenement << ", Quantité : " << b.quantite
                      << ", Prix total : " << b.prixTotal << ", Numéro de l'utilisateur : " << b.numeroUtilisateur << std::endl;
        }
    }
}

Utilisateur GestionnaireReservations::trouverUtilisateur(std::string nomUtilisateur) {
    for (const Utilisateur& u : utilisateurs) {
        if (u.nom == nomUtilisateur) {
            return u;
        }
    }
    throw std::invalid_argument("Utilisateur non trouvé");
}

void Application::demarrer() {
    std::cout << "Bienvenue dans l'application de réservation de billets !" << std::endl;
    std::cout << "Veuillez entrer vos informations pour commencer : " << std::endl;

    GestionnaireReservations gestionnaire;

    Evenement event1("Concert", "2023-11-15", 100, 30.0);
    Evenement event2("Conférence", "2023-11-20", 50, 20.0);

    gestionnaire.ajouterEvenement(event1);
    gestionnaire.ajouterEvenement(event2);

    std::string nom, prenom, dateNaissance, email;
    float solde;

    std::cout << "Entrez votre nom : ";
    std::cin >> nom;

    std::cout << "Entrez votre prénom : ";
    std::cin >> prenom;

    std::cout << "Entrez votre date de naissance (AAAA-MM-JJ) : ";
    std::cin >> dateNaissance;

    std::cout << "Entrez votre email : ";
    std::cin >> email;

    std::cout << "Entrez votre solde : ";
    std::cin >> solde;

    Utilisateur user(nom, prenom, dateNaissance, email, 1, solde);
    gestionnaire.ajouterUtilisateur(user);

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
    std::cout << "Mise à jour du solde : " << utilisateur.solde << " $" << std::endl;
}
