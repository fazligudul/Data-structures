//Fazlı Güdül
//Section 2
//22002785
#ifndef BIOLOGICALPATHWAY_H
#define BIOLOGICALPATHWAY_H

#include <iostream>
#include <string>
class BiologicalPathway{
    
public:
    BiologicalPathway();
    ~BiologicalPathway();
    
    void addPathway( const int pathwayId, const std::string pathwayName );
    void removePathway( const int pathwayId );
    void printPathways() const;
    void addProtein( const int proteinId, const int pathwayId );
    void removeProtein( const int proteinId, const int pathwayId );
    void printProteinsInPathway( const int pathwayId ) const;
    void addGene( const int geneID, const std::string geneName, const int proteinId );
    void removeGene( const int geneID, const int proteinId );
    void printGenesOfProtein( const int proteinId ) const;
    
private:
    struct Gene {
        int geneID;
        std::string geneName;
        Gene* next;

        Gene(int id, const std::string& name) {
            geneID=id;
            geneName=name;
            next=nullptr;
        }
    };

    struct Protein {
        int proteinID;
        Gene* genes;
        Protein* next;

        Protein(int id) {
            proteinID=id;
            genes=nullptr;
            next=nullptr;
        }
    };

    struct Pathway {
        int pathwayID;
        std::string pathwayName;
        Protein* proteins;
        Pathway* next;

        Pathway(int id, const std::string& name) {
            pathwayID=id;
            pathwayName=name;
            proteins=nullptr;
            next=nullptr;
        }
    };

    Pathway* pathways;
    Pathway* findPathway(const int pathwayId) const;
};

#endif // BIOLOGICALPATHWAY_H
