#include <ostream>
#include <fstream>
#include <string>
#include <cstring>

#include "cmatrix/src/matrix.h"

#include "truss.h"

std::string read_file(const char *file_name)
{
    std::string file_contents;
    std::ifstream file(file_name);
    if (file.fail()) {
        throw new std::runtime_error(std::string("File ") + std::string(file_name) + std::string(": ") + strerror(errno));
    }

    file.seekg(0, std::ios::end);
    file_contents.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    file_contents.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    return file_contents;
}

Truss::Truss()
{
    node         = new Node[MAX];
    klocal       = new cmatrix::Matrix<double>[MAX];
    connectivity = new char[MAX][MAX];
    knowledgeF   = new char[MAX];
    knowledgeu   = new char[MAX];
    locforce     = new cmatrix::Matrix<double>[MAX];
    area         = new double[MAX];
    length       = new double[MAX];
}


Truss::~Truss()
{
    delete[] node;
    delete[] klocal;
    delete[] connectivity;
    delete[] knowledgeF;
    delete[] knowledgeu;
    delete[] locforce;
    delete[] area;
    delete[] length;
}


// accepts the input data
void Truss::getData(const std::string file_contents)
{
    std::stringstream file(file_contents);

    total_members = 0; // the actual value is found in findKLocal()
    // the number of nodes
    file >> total_nodes;

    kglobal.setSize(2*total_nodes, 2*total_nodes);
    force.setSize(2*total_nodes, 1);
    displacement.setSize(2*total_nodes, 1);

    for (int i = 0; i < 2 * total_nodes; i++) {
        for (int j = 9; j < 2 * total_nodes; j++) {
            kglobal(i, j) = 0;
        }
    }

    for (int i = 0; i < total_nodes; i++) {
        // coordinates of the nodes
        file >> node[i].x >> node[i].y;
        connectivity[i][i] = 'n';  // avoids node being connected to itself

        // input forces
        // Is the force in x-direction known(y/n)?
        file >> knowledgeF[i*2];
        if (knowledgeF[i*2] == 'y') {
            file >> force(2*i, 0);
        }

        // Is the force in y-direction known(y/n)?
        file >> knowledgeF[i*2+1];
        if (knowledgeF[i*2+1] == 'y') {
            file >> force(2*i+1, 0);
        }

        // input displacement
        // Is the displacement in x-direction known(y/n)?
        file >> knowledgeu[i*2];
        if (knowledgeu[i*2] == 'y') {
            file >> displacement(2*i, 0);
        }

        // Is the displacement in y-direction known(y/n)?
        file >> knowledgeu[i*2+1];
        if (knowledgeu[i*2+1] == 'y') {
            file >> displacement(2*i+1, 0);
        }
    }

    int a = 0;
    for (int i = 0; i < total_nodes; i++) {
        for (int j = i + 1; j < total_nodes; j++) {
            // Is node i connected to node j (y/n)?;
            file >> connectivity[i][j];
            connectivity[j][i] = connectivity[i][j];
            // The area of the node (dummy value for optimization)
            if (connectivity[i][j] == 'y') {
                file >> area[a++];
            }
        }
    }
    // The value of E
    file >> E;
}


// finds all the local k matrices
void Truss::findKLocal()
{
    total_members = 0;
    double Cx, Cy, len;

    for(int i = 0; i < total_nodes; i++) {
        for(int j = i + 1; j < total_nodes; j++) {
            if(connectivity[i][j] == 'y' || connectivity[i][j] == 'Y') {
                length[total_members] = len = sqrt ( (node[i].x-node[j].x)*(node[i].x-node[j].x) + (node[i].y-node[j].y)*(node[i].y-node[j].y) );
                Cx = (node[j].x-node[i].x) / len;
                Cy = (node[j].y-node[i].y) / len;

                klocal[total_members].setSize(4, 4);
                klocal[total_members](0, 0) = klocal[total_members](2, 2) = Cx*Cx/len;
                klocal[total_members](1, 1) = klocal[total_members](3, 3) = Cy*Cy/len;
                klocal[total_members](0, 2) = klocal[total_members](2, 0) = -Cx*Cx/len;
                klocal[total_members](3, 1) = klocal[total_members](1, 3) = -Cy*Cy/len;
                klocal[total_members](0, 1) = klocal[total_members](1, 0) =
                        klocal[total_members](3, 2) = klocal[total_members](2, 3) = Cx*Cy/len;
                klocal[total_members](3, 0) = klocal[total_members](0, 3) =
                        klocal[total_members](1, 2) = klocal[total_members](2, 1) = -Cx*Cy/len;
                klocal[total_members] = klocal[total_members].scale(E*area[total_members]);
                total_members++;
            }
        }
    }
}

// finds the uncondensed k global matrix
void Truss::findKGlobal()
{
    int mem_no = 0;
    kglobal.fillWithZeros();
    for (int i = 0; i < total_nodes - 1; i++) {
        for (int j = i; j < total_nodes; j++) {
            if ((connectivity[i][j] == 'Y' || connectivity[i][j] == 'y') && i != j) {
                kglobal(i*2  , i*2  ) += klocal[mem_no](0, 0);
                kglobal(i*2  , i*2+1) += klocal[mem_no](0, 1);
                kglobal(i*2  , j*2  ) += klocal[mem_no](0, 2);
                kglobal(i*2  , j*2+1) += klocal[mem_no](0, 3);

                kglobal(i*2+1, i*2  ) += klocal[mem_no](1, 0);
                kglobal(i*2+1, i*2+1) += klocal[mem_no](1, 1);
                kglobal(i*2+1, j*2  ) += klocal[mem_no](1, 2);
                kglobal(i*2+1, j*2+1) += klocal[mem_no](1, 3);

                kglobal(j*2  , i*2  ) += klocal[mem_no](2, 0);
                kglobal(j*2  , i*2+1) += klocal[mem_no](2, 1);
                kglobal(j*2  , j*2  ) += klocal[mem_no](2, 2);
                kglobal(j*2  , j*2+1) += klocal[mem_no](2, 3);

                kglobal(j*2+1, i*2  ) += klocal[mem_no](3, 0);
                kglobal(j*2+1, i*2+1) += klocal[mem_no](3, 1);
                kglobal(j*2+1, j*2  ) += klocal[mem_no](3, 2);
                kglobal(j*2+1, j*2+1) += klocal[mem_no](3, 3);

                mem_no++;
            }
        }
    }
}

/* static condensation scheme to find k11, k12, k21 and k22
    as well as Fknown, Funknown, uknownand uknown*/
void Truss::condense()
{
    int count_fknown = 0, count_funknown = 0, count_uknown = 0, count_uunknown = 0;
    cmatrix::Matrix<double> temp(total_nodes*2, total_nodes*2);  // holds the force condensation
    kglobalcond.setSize(total_nodes*2, total_nodes*2);

    // condensing for forces
    // known forces at top
    for (int i = 0; i < 2 * total_nodes; i++) {
        if (knowledgeF[i] == 'y') {
            Fknown.mutateToInclude(force(i, 0), count_fknown, 0);
            for (int j = 0; j < 2 * total_nodes; j++) {
                temp.mutateToInclude(kglobal(i, j), count_fknown, j);
            }
            count_fknown++;
        }
    }

    // unknown forces at bottom
    for (int i = 0; i < 2 * total_nodes; i++) {
        if (knowledgeF[i] == 'n') {
            Funknown.mutateToInclude(force(i, 0), count_funknown, 0);
            for (int j = 0; j < 2 * total_nodes; j++)
                temp.mutateToInclude(kglobal(i, j), count_fknown+count_funknown, j);
            count_funknown++;
        }
    }

    //condensing for displacements
    // known displacements at the top
    for (int i = 0; i < 2 * total_nodes; i++) {
        if (knowledgeu[i] == 'y') {
            uknown.mutateToInclude(displacement(i, 0), count_uknown, 0);
            for (int j = 0; j < 2 * total_nodes; j++) {
                kglobalcond.mutateToInclude(temp(j, i), j, count_uknown);
            }
            count_uknown++;
        }
    }

    // unknown displacements at the bottom
    for (int i = 0; i < 2 * total_nodes; i++) {
        if (knowledgeu[i] == 'n') {
            uunknown.mutateToInclude(displacement(i, 0), count_uunknown, 0);
            for (int j = 0; j < 2 * total_nodes; j++) {
                kglobalcond.mutateToInclude(temp(j, i), j, count_uknown+count_uunknown);
            }
            count_uunknown++;
        }
    }

    k11.setSize(count_fknown, count_uknown);
    k12.setSize(count_fknown, count_uunknown);
    k21.setSize(count_funknown, count_uknown);
    k22.setSize(count_funknown, count_uunknown);

    // create the matrices K11, K12, K21 and K22
    // f known, u known
    for (int i = 0; i < count_fknown; i++) {
        for (int j = 0; j < count_uknown; j++) {
            k11(i, j) = kglobalcond(i, j);
        }
    }
    // f known, u unknown
    for (int i = 0; i < count_fknown; i++) {
        for (int j = 0; j < count_uunknown; j++) {
            k12(i, j) = kglobalcond(i, count_uknown+j);
        }
    }
    // f unknown, u known
    for (int i = 0; i < count_funknown; i++) {
        for (int j = 0; j < count_uknown; j++) {
            k21(i, j) = kglobalcond(count_fknown+i, j);
        }
    }
    // f unknown, u unknown
    for (int i = 0; i < count_funknown; i++) {
        for (int j = 0; j < count_uunknown; j++) {
            k22(i, j) = kglobalcond(count_fknown+i, count_uknown+j);
        }
    }
}


void Truss::solve()
{
    cmatrix::Matrix<double> k12inv = k12.invert();
    uunknown = k12inv * (Fknown - k11*uknown);
    Funknown = k21*uknown + k22*uunknown;

    cmatrix::Matrix<double> ulocal;
    uglobal.setSize(2*total_nodes, 1);
    ulocal.setSize(4, 1);

    // find global displacement matrix
    int a = 0, b = 0;
    for (int i = 0; i < 2 * total_nodes; i++) {
        if (knowledgeu[i] == 'y') {
            uglobal(i, 0) = uknown(a++, 0);
        } else {
            uglobal(i, 0) = uunknown(b++, 0);
        }
    }

    a = 0;
    for (int i = 0; i < total_nodes-1; i++) {
        // find all local displacement matrices
        for (int j = i + 1; j < total_nodes; j++) {
            if (connectivity[i][j] == 'y') {
                ulocal(0, 0) = uglobal(2*i  , 0);
                ulocal(1, 0) = uglobal(2*i+1, 0);
                ulocal(2, 0) = uglobal(2*j  , 0);
                ulocal(3, 0) = uglobal(2*j+1, 0);

                locforce[a] = klocal[a]*ulocal;
                a++;
            }
        }
    }
}


// Modify the area of the truss elements
void Truss::modifyArea(double new_area[])
{
    for (int i = 0; i<total_members; i++) {
        area[i] = new_area[i];
    }
}

std::ostream & operator << (std::ostream &out, const Truss &truss)
{
    out << "\n\nThe local k matrices are";
    for (int i = 0; i < truss.total_members; i++) {
        out << "\n\n\tklocal" << i << "\n" << truss.klocal[i];
    }

    out << "\n\n\nThe uncondensed global k matrix is\n" << truss.kglobal;
    out << "\n\n\nThe condensed global k matrix is\n" << truss.kglobalcond;

    out << "\n\n\n\t\tK11 = \n" << truss.k11 << "\n\n\t\tK12 = \n" << truss.k12
            << "\n\n\t\tK21 = \n" << truss.k21 << "\n\n\t\tK22 = \n" << truss.k22;

    out << "\n\nFknown = \n" << truss.Fknown;
    out << "\n\nUknown = \n" << truss.uknown;

    out << "\n\n\nUunknown = \n" << truss.uunknown;
    out << "\n\nFunknown = \n" << truss.Funknown;

    out << "\n\n\nThe forces in the members are";
    for (int i = 0; i < truss.total_members; i++) {
        out << "\n\nMember #" << i << "\n" << truss.locforce[i];
    }

    out << "\n\nThe global displacement matrix is\n" << truss.uglobal;

    return out;
}
