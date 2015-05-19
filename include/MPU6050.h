#ifndef MPU6050_H
#define MPU6050_H


class MPU6050
{
    public:
        MPU6050();

        double GetYRotation(double x, double y, double z);
        double GetYRotation(double x, double y, double z);

        void WakeUp

    protected:
    private:
        double Distance(double v1, double v2);



        def get_y_rotation(x,y,z):
    radians = math.atan2(x, dist(y,z))
    return -math.degrees(radians)

def get_x_rotation(x,y,z):
    radians = math.atan2(y, dist(x,z))
    return math.degrees(radians)

};

#endif // MPU6050_H
