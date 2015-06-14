#include "NdoVrt.h"

//GrafoGnr grafo;
int vcf = 5;// esto es para el vcf

NdoVrt::NdoVrt()
{
    //ctor
}

NdoVrt::~NdoVrt()
{
    //dtor
}


    GrafoGnr < V > ::E GrafoGnr< V >::obtEst(int vrt) const
    {
        if (xstVrt(vrt) == true)
        {
            return arrVrt[vrt].e;
        }
    }

    int GrafoGnr< V >::obtTmpChqVrs(int vrt) const
    {
        return arrVrt[vrt].tmpChqVrs;
    }

    int GrafoGnr< V >::obtCntChVrs(int vrt)const
    {

        return arrVrt[vrt].cntChqVrs;

    }

    void GrafoGnr< V >::modEst(int vrt, E ne)
    {
        if (xstVrt(vrt))
        {
            arrVrt[vrt].e = ne;
        }
    }

    void GrafoGnr< V >::modTmpChqVrs(int vrt, int nt)
    {
        if(xstVrt(vrt)) arrVrt[vrt].tmpChqVrs = nt;
    }


    void GrafoGnr< V >::actCntChqVrs(int vrt)
    {
        if(xstVrt(vrt)&& arrVrt[vrt].cntChqVrs == arrVrt[vrt].tmpChqVrs)
            arrVrt[vrt].cntChqVrs = 0;
        else
        {
            arrVrt[vrt].cntChqVrs++;
        }
    }


    void NdoVrt::infectar(int ios)
    {
        if (ios < obtTotVrt())
        {
            vector<int>infectemos;
            int randy;
            bool esta = true;
            for (int i = 0; i < ios; i++)
            {
                while (esta)
                {
                    randy = rand() % obtTotVrt();
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


    void GrafoGnr< V >::azarizarTmpChqVrs(int vcf)
    {
        int randy;
        for (int i = 0; i < obtTotVrt(); i++)
        {
            randy = rand() % vcf + 1;
            arrVrt[i].tmpChqVrs = randy;
        }
    }
