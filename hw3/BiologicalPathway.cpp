//Fazlı Güdül
//Section 2
//22002785
#include "BiologicalPathway.h"
using namespace std;

BiologicalPathway::BiologicalPathway(){
    pathways = nullptr;
}

BiologicalPathway::~BiologicalPathway() {
    // Deallocating memory for pathways
    while (pathways != nullptr) {
        Pathway* tempPathway = pathways;
        pathways = pathways->next;

        // Deallocating memory for proteins and genes
        Protein* tempProtein = tempPathway->proteins;
        while (tempProtein != nullptr) {
            Protein* tempProteinToDelete = tempProtein;
            tempProtein = tempProtein->next;

            Gene* tempGene = tempProteinToDelete->genes;
            while (tempGene != nullptr) {
                Gene* tempGeneToDelete = tempGene;
                tempGene = tempGene->next;
                delete tempGeneToDelete;
            }
            delete tempProteinToDelete;
        }
        delete tempPathway;
    }
}

void BiologicalPathway::addPathway(const int pathwayId, const string pathwayName) {
    Pathway* curr = pathways;
    while (curr != nullptr) {
        if (curr->pathwayID == pathwayId) {
            cout << "Cannot add pathway. There is already a pathway with ID " << pathwayId << "." << endl;
            return;
        }
        curr = curr->next;
    }

    // creating a new pathway
    Pathway* newPathway = new Pathway(pathwayId, pathwayName);

    // inserting new one to sorted linkedlist
    Pathway* prev = nullptr;
    curr = pathways;
    while (curr != nullptr && pathwayId > curr->pathwayID) {
        prev = curr;
        curr = curr->next;
    }
    if (prev == nullptr){
        // at starting
        newPathway->next = pathways;
        pathways = newPathway;
    } 
    else{
        // in end or middle
        prev->next = newPathway;
        newPathway->next = curr;
    }

    cout << "Added pathway " << pathwayId << "." << endl;
}
void BiologicalPathway::removePathway(const int pathwayId) {
    Pathway* prev = nullptr;
    Pathway* curr = pathways;

    // Finding which pathway to be removed 
    while (curr != nullptr && curr->pathwayID != pathwayId){
        prev = curr;
        curr = curr->next;
    }
    if (curr == nullptr){
        cout << "Cannot remove pathway. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }

    while (curr->proteins != nullptr) {
        Protein* tempProtein = curr->proteins;
        curr->proteins = curr->proteins->next;

        while (tempProtein->genes != nullptr) {
            Gene* tempGene = tempProtein->genes;
            tempProtein->genes = tempProtein->genes->next;
            delete tempGene;
        }

        delete tempProtein;
    }

    if (prev == nullptr) {
        pathways = curr->next;
    } 
    else{
        prev->next = curr->next;
    }
    delete curr;
    
    cout << "Removed pathway " << pathwayId << "." << endl;
}
void BiologicalPathway::printPathways() const{
    
    if (pathways == nullptr) {
        cout << "There are no pathways to show." << endl;
        return;
    }
    
    cout << "Pathways in the system:" << endl;
    Pathway* curr = pathways;
    
    while (curr != nullptr) {
        int proteinCount = 0;
        int geneCount = 0;

        Protein* proteinCurr = curr->proteins;
        while (proteinCurr != nullptr) {
            proteinCount++;
            Gene* geneCurr = proteinCurr->genes;
            while (geneCurr != nullptr) {
                geneCount++;
                geneCurr = geneCurr->next;
            }
            proteinCurr = proteinCurr->next;
        }

        cout << "Pathway " << curr->pathwayID << " : " << curr->pathwayName << " (" << proteinCount << " Proteins) (" << geneCount << " Genes)" << endl;
        curr = curr->next;
    }
}
BiologicalPathway::Pathway* BiologicalPathway::findPathway(const int pathwayId) const {
    Pathway* curr = pathways;
    while (curr != nullptr) {
        if (curr->pathwayID == pathwayId) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr; 
}
void BiologicalPathway::addProtein( const int proteinId, const int pathwayId ){
    Pathway* pathway = findPathway(pathwayId);
    if (pathway == nullptr) {
        cout << "Cannot add protein. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }

    Pathway* currPathway = pathways;
    while (currPathway != nullptr) {
        Protein* currProtein = currPathway->proteins;
        while (currProtein != nullptr) {
            if (currProtein->proteinID == proteinId) {
                cout << "Cannot add protein. There is a pathway having a protein with ID " << proteinId << "." << endl;
                return;
            }
            currProtein = currProtein->next;
        }
        currPathway = currPathway->next;
    }

    Protein* newProtein = new Protein(proteinId);

    Protein* prevProtein = nullptr;
    Protein* currProtein = pathway->proteins;
    
    while (currProtein != nullptr && proteinId > currProtein->proteinID) {
        prevProtein = currProtein;
        currProtein = currProtein->next;
    }
    if (prevProtein == nullptr){
        newProtein->next = pathway->proteins;
        pathway->proteins = newProtein;
    } 
    else{
        prevProtein->next = newProtein;
        newProtein->next = currProtein;
    }

    cout << "Added protein " << proteinId << " to pathway " << pathwayId << "." << endl;
}

void BiologicalPathway::removeProtein( const int proteinId, const int pathwayId ){
    Pathway* curr = pathways;

    while (curr != nullptr) {
        if (curr->pathwayID == pathwayId) {
            Protein* prev = nullptr;
            Protein* proteinCurr = curr->proteins;

            while ( proteinCurr != nullptr && proteinCurr->proteinID != proteinId ) {
                prev = proteinCurr;
                proteinCurr = proteinCurr->next;
            }
            if (proteinCurr == nullptr) {
                cout << "Cannot remove protein. Pathway " << pathwayId << " does not have a protein with ID " << proteinId << "." << endl;
                return;
            }
            // Deallocate memory for associated genes
            while (proteinCurr->genes != nullptr) {
                Gene* tempGene = proteinCurr->genes;
                proteinCurr->genes = proteinCurr->genes->next;
                delete tempGene;
            }

            if (prev == nullptr) {
                curr->proteins = proteinCurr->next;
            } 
            else{
                prev->next = proteinCurr->next;
            }
            delete proteinCurr;
            
            cout << "Removed protein " << proteinId << " from pathway " << pathwayId << "." << endl;
            return;
        }
        curr = curr->next;
    }

    cout << "Cannot remove protein. There is no pathway with ID " << pathwayId << "." << endl;
    }
void BiologicalPathway::printProteinsInPathway( const int pathwayId ) const{
    Pathway* curr = pathways;
    
    while (curr != nullptr) {
        if (curr->pathwayID == pathwayId) {
            if (curr->proteins == nullptr) {
                cout << "There are no proteins to show in pathway " << pathwayId << "." << endl;
                return;
            }
            cout << "Proteins in pathway " << pathwayId << ":" << endl;
            Protein* proteinCurr = curr->proteins;
            
            while (proteinCurr != nullptr) {
                cout << "Protein ID : " << proteinCurr->proteinID << ", Gene IDs : ";
                Gene* geneCurr = proteinCurr->genes;
                if (geneCurr == nullptr) {
                    cout << "None";
                }
                else{
                    cout<<"[";
                    while (geneCurr != nullptr) {
                        cout << geneCurr->geneID;
                        
                        if (geneCurr->next != nullptr) {
                            cout << ", ";
                        }
                        geneCurr = geneCurr->next;
                    }
                    cout<<"]";
                }
                cout << endl;
                proteinCurr = proteinCurr->next;
            }
            return;
        }
        curr = curr->next;
    }
    cout << "Cannot print proteins. There is no pathway with ID " << pathwayId << "." << endl;
}

void BiologicalPathway::addGene( const int geneID, const std::string geneName, const int proteinId ){
    
    Pathway* curr = pathways;
    while (curr != nullptr) {
        Protein* proteinCurr = curr->proteins;
        while (proteinCurr != nullptr) {
            Gene* geneCurr = proteinCurr->genes;
            while (geneCurr != nullptr) {
                if (geneCurr->geneID == geneID) {
                    cout << "Cannot add gene. Gene " << geneID << " is already in use." << endl;
                    return;
                }
                geneCurr = geneCurr->next;
            }
            proteinCurr = proteinCurr->next;
        }
        curr = curr->next;
    }

    curr = pathways;
    while (curr != nullptr) {
        
        Protein* proteinCurr = curr->proteins;
        while (proteinCurr != nullptr) {
            
            if (proteinCurr->proteinID == proteinId) {
                
                Gene* newGene = new Gene(geneID, geneName);
                Gene* prev = nullptr;
                Gene* geneCurr = proteinCurr->genes;
                while (geneCurr != nullptr && geneID > geneCurr->geneID) {
                    prev = geneCurr;
                    geneCurr = geneCurr->next;
                }
                if (prev == nullptr){
                
                    newGene->next = proteinCurr->genes;
                    proteinCurr->genes = newGene;
                } 
                else{
                   
                    prev->next = newGene;
                    newGene->next = geneCurr;
                }
                cout << "Added gene " << geneID << " to protein " << proteinId << "." << endl;
                return;
            }
            proteinCurr = proteinCurr->next;
        }
        curr = curr->next;
    }
    cout << "Cannot add gene. There is no protein with ID " << proteinId << "." << endl;
}
void BiologicalPathway::removeGene( const int geneID, const int proteinId ){
    Pathway* curr = pathways;

    while (curr != nullptr) {
        Protein* proteinCurr = curr->proteins;

        while (proteinCurr != nullptr) {
            if (proteinCurr->proteinID == proteinId) {
                Gene* prev = nullptr;
                Gene* geneCurr = proteinCurr->genes;

                while (geneCurr != nullptr && geneCurr->geneID != geneID) {
                    prev = geneCurr;
                    geneCurr = geneCurr->next;
                }
                if (geneCurr == nullptr) {
                    cout << "Cannot remove gene. There is no gene " << geneID << " encoding protein " << proteinId << "." << endl;
                    return;
                }

                if (prev == nullptr){
                    proteinCurr->genes = geneCurr->next;
                } 
                else{
                    prev->next = geneCurr->next;
                }
                delete geneCurr;
                
                cout << "Removed gene " << geneID << " from protein " << proteinId << "." << endl;
                return;
            }
            proteinCurr = proteinCurr->next;
        }
        curr = curr->next;
    }

    cout << "Cannot remove gene. There is no protein with ID " << proteinId << "." << endl;
}
void BiologicalPathway::printGenesOfProtein( const int proteinId ) const{
    Pathway* curr = pathways;
    while (curr != nullptr) {
        
        Protein* proteinCurr = curr->proteins;
        while (proteinCurr != nullptr) {
            
            if (proteinCurr->proteinID == proteinId) {
                if (proteinCurr->genes == nullptr) {
                    cout << "There are no genes to show in protein " << proteinId << "." << endl;
                    return;
                }
                cout << "Genes in protein " << proteinId << ":" << endl;
                Gene* geneCurr = proteinCurr->genes;
                while (geneCurr != nullptr) {
                    
                    cout << "GENE " << geneCurr->geneID << " : " << geneCurr->geneName << endl;
                    geneCurr = geneCurr->next;
                }
                return;
            }
            proteinCurr = proteinCurr->next;
        }
        curr = curr->next;
    }
    cout << "Cannot print genes. There is no protein with ID " << proteinId << "." << endl;
}

