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
            float prixUnitaire = ev.prix; // Utilisation du prix de l'événement
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
