#ifndef POSE
#define POSE

#include "heads.h"

class Pose
{
private:
    double data[40][3];
    double n_data[40][3];
    int clipID;
    int frameID;


public:
    double** getData()
    {
        return (double **)this->data;
    }
    int getClipID()
    {
        return clipID;
    }
    int getFrameID()
    {
        return frameID;
    }
    double** getnData()
    {
        return (double**)this->n_data;
    }

    void normalize(){
        double midPoint[3];
        memcpy(midPoint, this->data[2], sizeof(double)*3);
        double forwardPoint[3];
        double xAxi[3];
        for(int i=0;i<3;i++)
        {
            forwardPoint[i] = (this->data[4][i] + this->data[5][i])/2;
        }

        for(int i=0;i<3;i++)
        {
            xAxi[i] = forwardPoint[i] - midPoint[i];
        }

        xAxi[2] = .0;
        for(int i=0; i<40; i++)
        {
            this->n_data[i][0] = this->data[i][0] - midPoint[0];
            this->n_data[i][1] = this->data[i][1] - midPoint[1];
            this->n_data[i][2] = this->data[i][2] - midPoint[2];

            double tempx = this->n_data[i][0];
            double tempy = this->n_data[i][1];
            double cosx = xAxi[0]/sqrt(xAxi[0]*xAxi[0] + xAxi[1]*xAxi[1]);
            double sinx = xAxi[1]/sqrt(xAxi[0]*xAxi[0] + xAxi[1]*xAxi[1]);

            this->n_data[i][0] = tempx*cosx + tempy*sinx;
            this->n_data[i][1] = -tempx*sinx + tempy*cosx;
            }
        }

    void setData(double *rowData)
    {

        memcpy(this->data, rowData, sizeof(double)*120);
        this->clipID=(int)rowData[121];
        this->frameID=(int)rowData[122];

    }

    Pose(double *rowData)
    {
        this->setData(rowData);
        this->normalize();
    }

};

#endif // POSE
