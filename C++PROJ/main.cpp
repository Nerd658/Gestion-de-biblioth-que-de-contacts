#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Contact
{
public:
    string nom;
    string telephone;
    string email;
    string adresse;

    Contact(string n, string t, string e, string a)
        : nom(n), telephone(t), email(e), adresse(a) {}

    // Méthode afficher() marquée comme const pour pouvoir être appelée sur des objets const
    void afficher() const
    {
        cout << "Nom: " << nom << ", Telephone: " << telephone
             << ", Email: " << email << ", Adresse: " << adresse << endl;
    }
};

class BibliothequeContacts
{
private:
    vector<Contact> contacts;

public:
    void ajouterContact(const string &nom, const string &telephone, const string &email, const string &adresse)
    {
        contacts.push_back(Contact(nom, telephone, email, adresse));
    }

    void modifierContact(const string &nom)
    {
        for (auto &contact : contacts)
        {
            if (contact.nom == nom)
            {
                cout << "Modifier le telephone: ";
                cin >> contact.telephone;
                cout << "Modifier l'email: ";
                cin >> contact.email;
                cout << "Modifier l'adresse: ";
                cin >> contact.adresse;
                cout << "Contact modifié avec succès!" << endl;
                return;
            }
        }
        cout << "Contact non trouvé!" << endl;
    }

    void supprimerContact(const string &nom)
    {
        auto it = remove_if(contacts.begin(), contacts.end(), [&nom](const Contact &contact)
                            { return contact.nom == nom; });
        if (it != contacts.end())
        {
            contacts.erase(it, contacts.end());
            cout << "Contact supprimé avec succès!" << endl;
        }
        else
        {
            cout << "Contact non trouvé!" << endl;
        }
    }

    void rechercherContact(const string &nom)
    {
        for (const auto &contact : contacts)
        {
            if (contact.nom == nom)
            {
                contact.afficher();
                return;
            }
        }
        cout << "Contact non trouvé!" << endl;
    }

    void trierContacts()
    {
        sort(contacts.begin(), contacts.end(), [](const Contact &a, const Contact &b)
             { return a.nom < b.nom; });
        cout << "Contacts triés par nom!" << endl;
    }

    void sauvegarderContacts(const string &fichier)
    {
        ofstream out(fichier);
        if (out)
        {
            for (const auto &contact : contacts)
            {
                out << contact.nom << ";" << contact.telephone << ";" << contact.email << ";" << contact.adresse << endl;
            }
            cout << "Contacts sauvegardés!" << endl;
        }
        else
        {
            cout << "Erreur lors de l'ouverture du fichier!" << endl;
        }
    }

    void chargerContacts(const string &fichier)
    {
        ifstream in(fichier);
        if (in)
        {
            string ligne;
            while (getline(in, ligne))
            {
                stringstream ss(ligne);
                string nom, telephone, email, adresse;
                getline(ss, nom, ';');
                getline(ss, telephone, ';');
                getline(ss, email, ';');
                getline(ss, adresse, ';');
                ajouterContact(nom, telephone, email, adresse);
            }
            cout << "Contacts chargés!" << endl;
        }
        else
        {
            cout << "Erreur lors de l'ouverture du fichier!" << endl;
        }
    }

    void afficherContacts()
    {
        if (contacts.empty())
        {
            cout << "Aucun contact a afficher!" << endl;
            return;
        }
        for (const auto &contact : contacts)
        {
            contact.afficher();
        }
    }
};

int main()
{
    BibliothequeContacts bib;
    int choix;
    string nom, telephone, email, adresse, fichier;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Ajouter un contact\n";
        cout << "2. Modifier un contact\n";
        cout << "3. Supprimer un contact\n";
        cout << "4. Rechercher un contact\n";
        cout << "5. Trier les contacts\n";
        cout << "6. Sauvegarder les contacts\n";
        cout << "7. Charger les contacts\n";
        cout << "8. Afficher tous les contacts\n";
        cout << "9. Quitter\n";
        cout << "Entrez votre choix: ";
        cin >> choix;

        switch (choix)
        {
        case 1:
            cout << "Nom: ";
            cin >> nom;
            cout << "Telephone: ";
            cin >> telephone;
            cout << "Email: ";
            cin >> email;
            cout << "Adresse: ";
            cin >> adresse;
            bib.ajouterContact(nom, telephone, email, adresse);
            break;
        case 2:
            cout << "Nom du contact a modifier: ";
            cin >> nom;
            bib.modifierContact(nom);
            break;
        case 3:
            cout << "Nom du contact a supprimer: ";
            cin >> nom;
            bib.supprimerContact(nom);
            break;
        case 4:
            cout << "Nom du contact a rechercher: ";
            cin >> nom;
            bib.rechercherContact(nom);
            break;
        case 5:
            bib.trierContacts();
            break;
        case 6:
            cout << "Nom du fichier pour sauvegarder: ";
            cin >> fichier;
            bib.sauvegarderContacts(fichier);
            break;
        case 7:
            cout << "Nom du fichier a charger: ";
            cin >> fichier;
            bib.chargerContacts(fichier);
            break;
        case 8:
            bib.afficherContacts();
            break;
        case 9:
            cout << "Au revoir!" << endl;
            break;
        default:
            cout << "Choix invalide, essayez encore!" << endl;
        }
    } while (choix != 9);

    return 0;
}
