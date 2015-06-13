#include "NdoVrt.h"

GrafoGnr grafo;
    int vcf = 5;// esto es para el vcf

NdoVrt::NdoVrt()
{
    //ctor
}

NdoVrt::~NdoVrt()
{
    //dtor
}

NdoVrt::E NdoVrt::obtEst(int vrt) const
{
    if (xstVrt(vrt) == true)
    {
        return arrVrt[vrt].e;
    }
}


int NdoVrt::obtTmpChqVrs(int vrt) const
{
    return arrVrt[vrt].tmpChqVrs;
}

int NdoVrt::obtCntChVrs(int vrt)const {

    return arrVrt[vrt].cntChqVrs;

}
void NdoVrt::modEst(int vrt, E ne)
{
    if (grafo.xstVrt(vrt))
    {
        arrVrt[vrt].e = ne;
    }
}

void NdoVrt::modTmpChqVrs(int vrt, int nt)
{
    if(grafo.xstVrt(vrt)) arrVrt[vrt].tmpChqVrs = nt;
}

void NdoVrt::actCntChqVrs(int vrt)
{
    if(grafo.xstVrt(vrt)&& arrVrt[vrt].cntChqVrs == arrVrt[vrt].tmpChqVrs)
        arrVrt[vrt].cntChqVrs = 0;
    else
    {
        arrVrt[vrt].cntChqVrs++;
    }
}

void NdoVrt::infectar(int ios)
{
    if (ios < grafo.obtTotVrt())
    {
        vector<int>infectemos;
        int randy;
        bool esta = true;
        for (int i = 0; i < ios; i++)
        {
            while (esta)
            {
                randy = rand() % grafo.obtTotVrt();
                esta = false;
                for (int j = 0; j < infectemos.size(); j++)
                {
                    if(infectemos[j] == randy) esta = true;
                }
            }
            infectemos.push_back(randy);
            esta = true;
        }
        for (int i=0; i<infectemos.size(); i++)
        {
            arrVrt[infectemos[i]].e = I;
        }
    }
}


void NdoVrt::azarizarTmpChqVrs(int vcf)
{
    int randy;
    for (int i = 0; i < grafo.obtTotVrt(); i++)
    {
        randy = rand() % vcf + 1;
        arrVrt[i].tmpChqVrs = randy;
    }
}

void Grafo::modEstados(vector<NdoVrt>& stdAct)
{
}

