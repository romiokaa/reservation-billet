#ifndef RESERVBILLET_HPP
#define RESERVBILLET_HPP

#include <string>
#include <vector>
#include <iostream>

class Evenement {
public:
    std::string nom;
    std::string date;
    int placesDisponibles;
    float prix;

    Evenement() : nom(""), date(""), placesDisponibles(0), prix(0.0) {}

//    constructeur
    Evenement(std::string n, std::string d, int p, float pr) : nom(n), date(d), placesDisponibles(p), prix(pr) {}
};

class Utilisateur {
private:
    std::string nom;
    std::string prenom;
    std::string dateNaissance;
    std::string email;
    int numero;
    float solde;

public:
    Utilisateur(std::string n, std::string p, std::string d, std::string e, int num, float s) : nom(n), prenom(p), dateNaissance(d), email(e), numero(num), solde(s) {}
    
//Getters
    
    std::string getNom() const;
    
    std::string getPrenom() const;
    
    std::string getDateNaissance() const;
    
    std::string getEmail() const;
    
    int getNumero() const;
    
    float getSolde() const;
    
//Setters
    
    void setNom(std::string nouveauNom);
    
    void setPrenom(std::string nouveauPrenom);
    
    void setDateNaissance(std::string nouveauDateNaissance);
    
    void setEmail(std::string nouveauEmail);
    
    void setNumero(int nouveauNumero);
    
    void setSolde(float nouveauSolde);
};

class Billet {
public:
    int numero;
    std::string nomEvenement;
    int quantite;
    float prixTotal;
    int numeroUtilisateur;

    Billet(int num, std::string ne, int q, float pt, int nu) : numero(num), nomEvenement(ne), quantite(q), prixTotal(pt), numeroUtilisateur(nu) {}
};

class GestionnaireReservations {
private:
    std::vector<Evenement> evenements;
    std::vector<Utilisateur> utilisateurs;
    std::vector<Billet> billets;

public:
    void ajouterEvenement(Evenement e);
    void ajouterUtilisateur(Utilisateur u);
    void reserverBillets(Utilisateur& u, Evenement e, int nbBillets);
    void afficherEvenementsAvecPlacesEtPrix();
    void afficherBilletsUtilisateur(Utilisateur u);
    Utilisateur trouverUtilisateur(std::string nomUtilisateur);

    const std::vector<Evenement>& getEvenements() const {
        return evenements;
    }
};

class Application {
private:
    GestionnaireReservations gestionnaire;

public:
    void demarrer();
};

#endif
