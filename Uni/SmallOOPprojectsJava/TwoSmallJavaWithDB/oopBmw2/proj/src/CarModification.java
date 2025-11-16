public class CarModification {
    private int carId;
    private String modelName;
    private int turboId;
    private int exhaustId;
    private int intakeId;

    public CarModification(int carId, String modelName, int turboId, int exhaustId, int intakeId) {
        this.carId = carId;
        this.modelName = modelName;
        this.turboId = turboId;
        this.exhaustId = exhaustId;
        this.intakeId = intakeId;
    }

    public int getCarId() {
        return carId;
    }

    public String getModelName() {
        return modelName;
    }

    public int getTurboId() {
        return turboId;
    }

    public int getExhaustId() {
        return exhaustId;
    }

    public int getIntakeId() {
        return intakeId;
    }

    @Override
    public String toString() {
        return modelName + " with Turbo ID: " + turboId + ", Exhaust ID: " + exhaustId + ", Intake ID: " + intakeId;
    }

    public int HPCalculation(int Hp, int add1, int add2, int add3){
        int quarterCalculated;
        quarterCalculated = Hp + add1 + add2 + add3;
        return quarterCalculated;
    }

    //public int

}
