//----------------------------------------------------------------------------//
//                  *** ДВИЖОК ГЕОИНФОРМАЦИОННОЙ СИСТЕМЫ ***                  //
//                                                                            //
// Файл Cartography.h                                                         //
//                                                                            //
//            *** TCARTOGRAPHY КАРТОГРАФИЧЕСКИЕ ПРЕОБРАЗОВАНИЯ ***            //
//                                                                            //
// Автор ГЛУЩЕНКО Сергей                                                      //
//                                                                            //
//                                                                     Москва //
//----------------------------------------------------------------------------//


#ifndef CartographyH
#define CartographyH

#include "../QuatVectMatr/GeneralLib.h"


class TCartography
{
  private:
    //Переводит геоцентрическую широту в геодезическую широту с учетом превышения объекта над Общеземным эллипсоидом
    //Формула принята "Международным геодезическим и географическим союзом" в Канберре в 1979 году
    double FiToB(double Fi, double H);

    //Переводит геодезическую широту в геоцентрическую широту с учетом превышения объекта над Общеземным эллипсоидом
    //Формула принята "Международным геодезическим и географическим союзом" в Канберре в 1979 году
    double BToFi(double B, double H);

    //Переводит одну координату X из отрезка [A; B] в координату из отрезка [Alpha; Betta]
    // По сути производится растяжение или сжатие одномерного пространства
    // "B" должен быть строго больше "A"
    double Strain(double X, double A, double B, double Alpha, double Betta);

    //Возвращает координаты заданной точки в середине маршрута. Точки начала, конца маршрута и искомая точка
    // лежат на поверхности Оскулирующей Земли (то есть их превышения над этой оскулирующей землей нулевые).
    // Оскулирующая Земля опеределяется своими полуосями. Искомая точка задается с помощью угла Corner, отсчиты-
    // ваемого от точки начала маршрута в сторону точки конца маршрута. Corner - это плоский угол мажду вектора-
    // ми StartPoint и MiddlePoint
    bool MiddlePointOnRoute(double Corner, TVector StartPoint, TVector StopPoint, double AEarthOskul,
                            double BEarthOskul, TVector* MiddlePoint);

  protected:
    //Цилиндрическая равнопромежуточная проекция
    // Переводит сферические геоцентрические координаты {Fi; Lambda} в плановые декартовы координаты {X; Y}
    // На вход подаются:
    // - геоцентрическая широта Fi [рад];
    // - геоцентрическая долгота Lambda [рад].
    // На выходе можно получить:
    // - абсциссу X плановых координат в цилиндрической равнопромежуточной проекции;
    // - ординату Y плановых координат в цилиндрической равнопромежуточной проекции
    void FiLambdaToCylindricalEqualSpaceXY(double Fi, double Lambda, double* X, double* Y);

    //Цилиндрическая равнопромежуточная проекция
    // Переводит плановые декартовы координаты {X; Y} в сферические геоцентрические координаты {Fi; Lambda}
    // На вход подаются:
    // - абсцисса X плановых координат в цилиндрической равнопромежуточной проекции;
    // - ордината Y плановых координат в цилиндрической равнопромежуточной проекции.
    // На выходе можно получить:
    // - геоцентрическую широту Fi [рад];
    // - геоцентрическую долготу Lambda [рад]
    void CylindricalEqualSpaceXYToFiLambda(double X, double Y, double* Fi, double* Lambda);

    //Азимутальная ортографическая проекция Северного Полюса
    // Переводит сферические геоцентрические координаты {Fi; Lambda} в плановые декартовы координаты {X; Y}
    // На вход подаются:
    // - геоцентрическая широта Fi [рад];
    // - геоцентрическая долгота Lambda [рад].
    // На выходе можно получить:
    // - абсциссу X плановых координат в азимутальной ортографической проекции Северного Полюса;
    // - ординату Y плановых координат в азимутальной ортографической проекции Северного Полюса
    void FiLambdaToAzimuthOrthographicNorthXY(double Fi, double Lambda, double* X, double* Y);

    //Азимутальная ортографическая проекция Северного Полюса
    // Переводит плановые декартовы координаты {X; Y} в сферические геоцентрические координаты {Fi; Lambda}
    // На вход подаются:
    // - абсцисса X плановых координат в азимутальной ортографической проекции Северного Полюса;
    // - ордината Y плановых координат в азимутальной ортографической проекции Северного Полюса.
    // На выходе можно получить:
    // - геоцентрическую широту Fi [рад];
    // - геоцентрическую долготу Lambda [рад]
    void AzimuthOrthographicNorthXYToFiLambda(double X, double Y, double* Fi, double* Lambda);

    //Азимутальная ортографическая проекция Южного Полюса
    // Переводит сферические геоцентрические координаты {Fi; Lambda} в плановые декартовы координаты {X; Y}
    // На вход подаются:
    // - геоцентрическая широта Fi [рад];
    // - геоцентрическая долгота Lambda [рад].
    // На выходе можно получить:
    // - абсциссу X плановых координат в азимутальной ортографической проекции Южного Полюса;
    // - ординату Y плановых координат в азимутальной ортографической проекции Южного Полюса
    void FiLambdaToAzimuthOrthographicSouthXY(double Fi, double Lambda, double* X, double* Y);

    //Азимутальная ортографическая проекция Южного Полюса
    // Переводит плановые декартовы координаты {X; Y} в сферические геоцентрические координаты {Fi; Lambda}
    // На вход подаются:
    // - абсцисса X плановых координат в азимутальной ортографической проекции Южного Полюса;
    // - ордината Y плановых координат в азимутальной ортографической проекции Южного Полюса.
    // На выходе можно получить:
    // - геоцентрическую широту Fi [рад];
    // - геоцентрическую долготу Lambda [рад]
    void AzimuthOrthographicSouthXYToFiLambda(double X, double Y, double* Fi, double* Lambda);

    //Равноугольная цилиндрическая проекция Меркатора
    // Переводит сферические геоцентрические координаты {Fi; Lambda} в плановые декартовы координаты {X; Y}
    // На вход подаются:
    // - геоцентрическая широта Fi [рад];
    // - геоцентрическая долгота Lambda [рад].
    // На выходе можно получить:
    // - абсциссу X плановых координат в проекции Меркатора;
    // - ординату Y плановых координат в проекции Меркатора
    void FiLambdaToMercatorXY(double Fi, double Lambda, double* X, double* Y);

    //Равноугольная цилиндрическая проекция Меркатора
    // Переводит плановые декартовы координаты {X; Y} в сферические геоцентрические координаты {Fi; Lambda}
    // На вход подаются:
    // - абсцисса X плановых координат в проекции Меркатора;
    // - ордината Y плановых координат в проекции Меркатора.
    // На выходе можно получить:
    // - геоцентрическую широту Fi [рад];
    // - геоцентрическую долготу Lambda [рад]
    void MercatorXYToFiLambda(double X, double Y, double* Fi, double* Lambda);

    //Псевдоцилиндрическая проекция Каврайского
    // Переводит сферические геоцентрические координаты {Fi; Lambda} в плановые декартовы координаты {X; Y}
    // На вход подаются:
    // - геоцентрическая широта Fi [рад];
    // - геоцентрическая долгота Lambda [рад].
    // На выходе можно получить:
    // - абсциссу X плановых координат в проекции Каврайского;
    // - ординату Y плановых координат в проекции Каврайского
    void FiLambdaToKavrayskiyXY(double Fi, double Lambda, double* X, double* Y);

    //Псевдоцилиндрическая проекция Каврайского
    // Переводит плановые декартовы координаты {X; Y} в сферические геоцентрические координаты {Fi; Lambda}
    // На вход подаются:
    // - абсцисса X плановых координат в проекции Каврайского;
    // - ордината Y плановых координат в проекции Каврайского.
    // На выходе можно получить:
    // - геоцентрическую широту Fi [рад];
    // - геоцентрическую долготу Lambda [рад]
    void KavrayskiyXYToFiLambda(double X, double Y, double* Fi, double* Lambda);

    //Переводит геодезические координаты {B; L} эллипсоида ПЗ-90 в сферические геоцентрические координаты {Fi; Lambda}
    // На вход подаются:
    // - геодезическая широта B [рад];
    // - геодезическая долгота L [рад];
    // - превышение над общеземным эллипсоидом [м].
    // На выходе можно получить:
    // - геоцентрическую широту Fi [рад];
    // - геоцентрическую долготу Lambda [рад]
    void PZ90BLToFiLambda(double B, double L, double H, double* Fi, double* Lambda);

    //Переводит сферические геоцентрические координаты {Fi; Lambda} в геодезические координаты {B; L} эллипсоида ПЗ-90
    // На вход подаются:
    // - геоцентрическая широта Fi [рад];
    // - геоцентрическая долгота Lambda [рад];
    // - превышение над общеземным эллипсоидом [м].
    // На выходе можно получить:
    // - геодезическая широта B [рад];
    // - геодезическая долгота L [рад]
    void FiLambdaToPZ90BL(double Fi, double Lambda, double H, double* B, double* L);

    //Переводит сценические координаты в плановые координаты текущей проекции
    // На вход подаются:
    // - абсцисса ScreenX сценических координат;
    // - ордината ScreenY сценических координат.
    // На выходе можно получить:
    // - абсцисса X плановых координат в текущей проекции;
    // - ордината Y плановых координат в текущей проекции
    void ScreenXYToProjectionXY(double ScreenX, double ScreenY, double* X, double* Y);

    //Переводит плановые координаты текущей проекции в сценические координаты
    // На вход подаются:
    // - абсцисса X плановых координат в текущей проекции;
    // - ордината Y плановых координат в текущей проекции.
    // На выходе можно получить:
    // - абсцисса ScreenX сценических координат;
    // - ордината ScreenY сценических координат
    void ProjectionXYToScreenXY(double X, double Y, double* ScreenX, double* ScreenY);

  public:
    TCartography(void);
    virtual ~TCartography(void);

    //Безопасный арксинус
    static double ArcSin(double Value);

    //Безопасный тангенс (безопасно работает с углами близкими к 90 градусам)
    static double Tan(double Value);

    //Безопасный арктангенс, возвращающий результат в диапазоне от -Pi до +Pi радиан
    static double ArcTan2(double Y, double X);

    //Возвращает целую часть числа.
    //Число Value должно быть таким, чтобы по размерности его целая часть могла быть сохранена в типе int
    static int Trunc(double Value);

    //Перевод из Геодезической сферической CK в Гринвичскую СК
    static void BLHToOtn(double B, double L, double H, TVector* R);

    //Перевод из Гринвичской СК в Геодезическую сферическую СК
    static void OtnToBLH(TVector R, double* B, double* L, double* H);

    //Переводит сценические координаты {ScreenX; ScreenY} в геодезические координаты {B; L} [рад] эллипсоида ПЗ-90,
    // используя текущую проекцию
    // На вход подаются:
    // - абсцисса ScreenX сценических координат;
    // - ордината ScreenY сценических координат.
    // На выходе можно получить:
    // - геодезическая широта B [рад];
    // - геодезическая долгота L [рад]
    void ScreenXYToPZ90BL(double ScreenX, double ScreenY, double* B, double* L);

    //Переводит геодезические координаты {B; L} [рад] эллипсоида ПЗ-90 в сценические координаты {ScreenX; ScreenY},
    // используя текущую проекцию
    // На вход подаются:
    // - геодезическая широта B [рад];
    // - геодезическая долгота L [рад].
    // На выходе можно получить:
    // - абсцисса ScreenX сценических координат;
    // - ордината ScreenY сценических координат
    void PZ90BLToScreenXY(double B, double L, double* ScreenX, double* ScreenY);

    //Вычисляет длину геодезической линии между указанными точками
    // На вход подаются:
    // - геодезическая широта B начала линии [рад];
    // - геодезическая долгота L начала линии [рад];
    // - геодезическая широта B конца линии [рад];
    // - геодезическая долгота L конца линии [рад]
    // На выходе можно получить:
    // - длину геодезической линии на эллипсоиде ПЗ-90 [м]
    double RulerLength(double StartB, double StartL, double StopB, double StopL);

    void* OWNER;   //Обязателен к заполнению

    double RZEkv;  //Экваториальный радиус Земли из ПЗ-90.02
    double ALPHA;  //Сжатие Земного эллипсоида из ПЗ-90.02
};


#endif
