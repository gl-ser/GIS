# GIS
Движок геоинформационной системы

Использует функционал:

- Qt 5;
- кватернионно-векторно-матричной библиотеки [QuatVectMatr](https://github.com/gl-ser/QuatVectMatr);
- библиотеки логических манипуляций над множествами [Multitude](https://github.com/gl-ser/Multitude).

Реализует основные возможности геоинформационной системы, необходимые для создания приложений, интерфейс пользователя которых основан на действиях с электронной картой местности.

Состоит из 8 классов: TCartography, TView, TScene, TFrame, TLayer, TMapData, TGISLib, TShellGIS.

---

### 1. TCartography класс картографических преобразований
Является основным аппаратом вычислительной математики в движке геоинформационной системы.

#### Публичные методы
1.1. _ScreenXYToPZ90BL_ переводит сценические координаты в геодезические координаты эллипсоида ПЗ-90, используя текущую проекцию

На вход подаются:

  - абсцисса ScreenX сценических координат;
  - ордината ScreenY сценических координат.

На выходе можно получить:

  - геодезическая широта B [рад];
  - геодезическая долгота L [рад].

Синтаксис:

```cpp
void ScreenXYToPZ90BL(double ScreenX, double ScreenY, double* B, double* L)
```

1.2. _PZ90BLToScreenXY_ переводит геодезические координаты эллипсоида ПЗ-90 в сценические координаты, используя текущую проекцию

На вход подаются:

  - геодезическая широта B [рад];
  - геодезическая долгота L [рад].

На выходе можно получить:

  - абсцисса ScreenX сценических координат;
  - ордината ScreenY сценических координат.

Синтаксис:

```cpp
void PZ90BLToScreenXY(double B, double L, double* ScreenX, double* ScreenY)
```

1.3. _RulerLength_ вычисляет длину геодезической линии между указанными точками

На вход подаются:

  - геодезическая широта B начала линии [рад];
  - геодезическая долгота L начала линии [рад];
  - геодезическая широта B конца линии [рад];
  - геодезическая долгота L конца линии [рад].

На выходе можно получить:

  - длину геодезической линии на эллипсоиде ПЗ-90 [м].

Синтаксис:

```cpp
double RulerLength(double StartB, double StartL, double StopB, double StopL)
```

#### Публичное свойство
1.4. _OWNER_ свойство Указатель на объект класса-владельца

Синтаксис:

```cpp
void* OWNER
```

---

### 2. TView класс, реализующий «вид» для отрисовки картографической сцены
Расширяет возможности «вида» из Qt для отрисовки картографической сцены.

#### Публичный тип
```cpp
//Инструменты по работе с картой
enum TTool
{
  MOVE = 1,   //Движение карты
  RULER = 2,  //Линейка
  ARROW = 3   //Стрелка
};
```
#### Публичные методы
2.1. _SetCursor_ устанавливает вид курсора в соответствии с инструментом по работе с картой

Синтаксис:

```cpp
void SetCursor(TTool Value)
```

2.2. _CloseHint_ закрывает всплывающую подсказку

Синтаксис:

```cpp
void CloseHint(void)
```
#### Публичное свойство
2.3. _OWNER_ свойство Указатель на объект класса-владельца

Синтаксис:

```cpp
void* OWNER
```

---

### 3. TScene класс графической сцены
Расширяет возможности графической сцены из Qt.
#### Публичный сигнал
3.1. _GetDataRightMouse_ сигнал Обработка события щелчка правой кнопки "мыши"

Возвращает экранные и геодезические координаты, список объектов карты по координатам

Синтаксис:

```cpp
void GetDataRightMouse(QPoint Value1, TOnePoint Value2, TMapData::TObjList Objects)
```

#### Публичное свойство
3.2. _OWNER_ свойство Указатель на объект класса-владельца

Синтаксис:

```cpp
void* OWNER
```

---

### 4. TFrame класс, реализующий рамку карты и 15-градусную сетку
#### Публичные методы
4.1. _Add_ добавить рамку на карту

Синтаксис:

```cpp
void Add(void)
```

4.2. _Del_ удалить рамку карты

Синтаксис:

```cpp
void Del(void)
```

4.3. _RePaint_ перерисовать рамку

Синтаксис:

```cpp
void RePaint(void)
```

4.4. _AddGrid_ добавить 15-градусную сетку на карту

Синтаксис:

```cpp
void AddGrid(void)
```

4.5. _DelGrid_ удалить 15-градусную сетку

Синтаксис:

```cpp
void DelGrid(void)
```

4.6. _RePaintGrid_ перерисовать 15-градусную сетку

Синтаксис:

```cpp
void RePaintGrid(void)
```

4.7. _GetGrid_ возвращает 15-градусную сетку

Синтаксис:

```cpp
TArraySpot GetGrid(void)
```

#### Публичное свойство
4.8. _OWNER_ свойство Указатель на объект класса-владельца

Синтаксис:

```cpp
void* OWNER
```

---

### 5. TLayer класс картографического слоя
Слой – основное понятие, с которым сталкивается пользователь при выведении графической информации на электронную карту.
#### Публичные типы

```cpp
//Тип символа, изображающего объект "точка" в слое
enum TTypeSymbol
{
  NONE_SYMBOL = 0,    //Не задан
  CIRCLE_SYMBOL = 1,  //Круг
  RECT_SYMBOL = 2     //Квадрат
};


//Тип объекта в слое
enum TTypeObj
{
  NONE_OBJ = 0,      //Не задан
  POINT_OBJ = 1,     //Точка
  POLYLINE_OBJ = 2,  //Полилиния
  REGION_OBJ = 3     //Регион
};


//Полушарие Земли, в котором располагается объект
enum THemisphere
{
  NONE_HEM = 0,   //Не задано
  NORTH_HEM = 1,  //Северное полушарие
  SOUTH_HEM = 2,  //Южное полушарие
  BOTH_HEM = 3    //Оба полушария (северное и южное)
};


//Тип описывает параметры объекта "точка" в слое
struct ObjPoint
{
  ObjPoint() : Type(NONE_SYMBOL), Pen(NULL), Brush(NULL) {}
  TTypeSymbol Type;  //Тип символа, изображающего объект "точка"
  TOnePoint Point;   //Геодезические координаты объекта "точка"
  QPen *Pen;         //Перо для рисования объекта "точка"
  QBrush *Brush;     //Заливка для рисования объекта "точка"
};
typedef struct ObjPoint TObjPoint;


//Тип описывает параметры объекта "полилиния" в слое
struct ObjPolyLine
{
  ObjPolyLine() : Pen(NULL) {}
  TSpot Spot;  //Геодезические координаты узловых точек полилинии
  QPen *Pen;   //Перо для рисования объекта "полилиния"
};
typedef struct ObjPolyLine TObjPolyLine;


//Тип описывает параметры объекта "регион" в слое
struct ObjRegion
{
  ObjRegion() : Pen(NULL), Brush(NULL) {}
  TSpot Spot;     //Геодезические координаты узловых точек региона
  QPen *Pen;      //Перо для рисования объекта "регион"
  QBrush *Brush;  //Заливка для рисования объекта "регион"
};
typedef struct ObjRegion TObjRegion;


//Тип описывает заголовок одного объекта в слое
struct HeaderOfObj
{
  HeaderOfObj() : ID(0), Name("") {}
  unsigned int ID;   //Идентификатор объекта
  std::string Name;  //Наименование объекта
};
typedef struct HeaderOfObj THeaderOfObj;


//Тип описывает все заголовки объектов в слое
typedef std::vector<THeaderOfObj> THeadersObjects;


//Тип описывает параметры одного объекта в слое
struct Obj
{
  Obj() : HandlePointAsEllipse(NULL), HandlePointAsRect(NULL), 
          HandleRegion(NULL), HandlePolyLine(NULL), Hemisphere(NONE_HEM), 
          Type(NONE_OBJ) {}
  QGraphicsEllipseItem *HandlePointAsEllipse;  //Указатель на item кружочка, 
          // помещенного на сцену. Пользователь не заполняет
  QGraphicsRectItem *HandlePointAsRect;  //Указатель на item квадрата, 
          // помещенного на сцену. Пользователь не заполняет
  QGraphicsPolygonItem *HandleRegion;  //Указатель на item полигона, 
          // помещенного на сцену. Пользователь не заполняет
  QGraphicsPathItem *HandlePolyLine;  //Указатель на item полилинии, 
          // помещенной на сцену. Пользователь не заполняет
  THeaderOfObj Header;     //Заголовок объекта
  THemisphere Hemisphere;  //Полушарие Земли, в котором располагается объект
  TTypeObj Type;           //Тип объекта
  TObjPoint Point;         //Тип объекта POINT_OBJ - "точка"
  TObjPolyLine PolyLine;   //Тип объекта POLYLINE_OBJ - "полилиния"
  TObjRegion Region;       //Тип объекта REGION_OBJ - "регион"
};
typedef struct Obj TObj;


//Тип описывает параметры всех объектов в слое
typedef std::vector<TObj> TObjects;
```

#### Публичные методы
5.1. _RGBToMI_ переводит цвета R, G, B в код цвета MapInfo

На вход подаются:

  - красный;
  - зеленый;
  - синий.

На выходе можно получить:

  - цвет в формате MapInfo.

Синтаксис:

```cpp
void RGBToMI(int R, int G, int B, int* MI)
```

5.2. _MIToRGB_ переводит цвета R, G, B в код цвета MapInfo

На вход подаются:

  - цвет в формате MapInfo.

На выходе можно получить:

  - красный;
  - зеленый;
  - синий.

Синтаксис:

```cpp
void MIToRGB(int MI, int* R, int* G, int* B)
```

5.3. _PenMIToQPen_ переводит перо формата MapInfo в формат QPen

На вход подаются:

  - ширина линии в формате MapInfo;
  - тип линии в формате MapInfo;
  - цвет линии в формате MapInfo.

На выходе можно получить:

  - перо QPen.

Синтаксис:

```cpp
QPen PenMIToQPen(int WidthMI, int PatternMI, int ColorMI)
```

5.4. _BrushMIToQBrush_ переводит заливку формата MapInfo в формат QBrush

На вход подаются:

  - тип штриховки в формате MapInfo;
  - цвет штриховки в формате MapInfo.

На выходе можно получить:

  - заливку QBrush.

Синтаксис:

```cpp
QBrush BrushMIToQBrush(int PatternMI, int ColorMI)
```

5.5. _RePaint_ быстро перерисовать слой

Синтаксис:

```cpp
void RePaint(void)
```

5.6. _CoolRePaint_ перерисовать слой путем удаления и создания всех его объектов

Синтаксис:

```cpp
void CoolRePaint(void)
```

5.7. _Hide_ скрыть (девизуализировать) слой

Синтаксис:

```cpp
void Hide(void)
```

5.8. _Show_ показать (визуализировать) слой

Синтаксис:

```cpp
void Show(void)
```

5.9. _GetVisible_ возвращает признак визуализации слоя

Синтаксис:

```cpp
bool GetVisible(void)
```

5.10. _GetStringObj_ возвращает строку (содержащую имя слоя и имя объекта) по указателю, если такой объект найдется в слое

Синтаксис:

```cpp
std::string GetStringObj(QGraphicsItem* ID)
```

5.11. _GetHeaderObj_ возвращает заголовок объекта по указателю, если такой объект найдется в слое

Синтаксис:

```cpp
THeaderOfObj GetHeaderObj(QGraphicsItem* ID)
```

5.12. _GetFreeID_ возвращает минимальное свободное значение идентификатора для размещения нового объекта в слое

На выходе можно получить:

  - свободное значение идентификатора объекта.

Синтаксис:

```cpp
unsigned int GetFreeID(void)
```

5.13. _GetObjList_ возвращает список заголовков объектов в слое

Синтаксис:

```cpp
THeadersObjects GetObjList(void)
```

5.14. _FindObj_ ищет объект, обратившись к нему по идентификатору

Синтаксис:

```cpp
int FindObj(unsigned int ID);
```

5.15. _AddPolyLineQuick_ добавляет в слой объект типа "полилиния"

Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint.

На вход подаются:

  - идентификатор объекта;
  - наименование объекта;
  - геодезические координаты узловых точек полилинии на эллипсоиде ПЗ-90 [рад];
  - перо для рисования объекта "полилиния".

Синтаксис:

```cpp
void AddPolyLineQuick(unsigned int ID, std::string Name, TSpot Spot, QPen Pen)
```

5.16. _AddRegionQuick_ добавляет в слой объект типа "регион"

Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint.

На вход подаются:

  - идентификатор объекта;
  - наименование объекта;
  - геодезические координаты узловых точек региона на эллипсоиде ПЗ-90 [рад];
  - перо для рисования объекта "регион";
  - заливка для рисования объекта "регион".

Синтаксис:

```cpp
void AddRegionQuick(unsigned int ID, std::string Name, TSpot Spot, QPen Pen, QBrush Brush)
```

5.17. _AddPointQuick_ добавляет в слой объект типа "точка"

Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint.

На вход подаются:

  - идентификатор объекта;
  - наименование объекта;
  - тип символа, изображающего объект "точка";
  - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад];
  - перо для рисования объекта "точка";
  - заливка для рисования объекта "точка".

Синтаксис:

```cpp
void AddPointQuick(unsigned int ID, std::string Name, TTypeSymbol Type, 
                   TOnePoint Point, QPen Pen, QBrush Brush)
```

5.18. _AddPoint_ добавляет в слой объект типа "точка"

Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint.

На вход подаются:

  - идентификатор объекта;
  - наименование объекта;
  - тип символа, изображающего объект "точка";
  - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад];
  - перо для рисования объекта "точка";
  - заливка для рисования объекта "точка".

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки.

Синтаксис:

```cpp
bool AddPoint(unsigned int ID, std::string Name, TTypeSymbol Type, 
              TOnePoint Point, QPen Pen, QBrush Brush)
```

5.19. _AddPolyLine_ добавляет в слой объект типа "полилиния"

Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint.

На вход подаются:

  - идентификатор объекта;
  - наименование объекта;
  - геодезические координаты узловых точек полилинии на эллипсоиде ПЗ-90 [рад];
  - перо для рисования объекта "полилиния".

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки.

Синтаксис:

```cpp
bool AddPolyLine(unsigned int ID, std::string Name, TSpot Spot, QPen Pen)
```

5.20. _AddRegion_ добавляет в слой объект типа "регион"

Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint.

На вход подаются:

  - идентификатор объекта;
  - наименование объекта;
  - геодезические координаты узловых точек региона на эллипсоиде ПЗ-90 [рад];
  - перо для рисования объекта "регион";
  - заливка для рисования объекта "регион".

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки.

Синтаксис:

```cpp
bool AddRegion(unsigned int ID, std::string Name, TSpot Spot, QPen Pen, QBrush Brush)
```

5.21. _DelObj_ удаляет объект любого типа из слоя

На вход подаются:

  - идентификатор объекта.

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки.

Синтаксис:

```cpp
bool DelObj(unsigned int ID)
```

#### Публичные свойства
5.22. _Objects_ свойство Объекты, содержащиеся в слое

Синтаксис:

```cpp
TObjects Objects
```

5.23. _Name_ свойство Имя слоя (обязательно к заполнению)

Синтаксис:

```cpp
std::string Name
```

5.24. _OWNER_ свойство Указатель на объект класса-владельца

Синтаксис:

```cpp
void* OWNER
```

---

### 6. TMapData класс картографических данных
Класс является держателем всех картографических данных, которые пользователь размещает на карте.
#### Публичные типы

```cpp
//Тип описывает список слоев (не сами слои)
struct OneLayer
{
  OneLayer() : Name(""), Visible(false) {}
  std::string Name;
  bool Visible;
};
typedef std::vector<struct OneLayer> TLayerList;


//Тип описывает возвращаемый из карты список объектов
struct Obj
{
  Obj() : LayerName(""), ObjID(0), ObjName("") {}
  std::string LayerName;  //Имя слоя
  unsigned int ObjID;     //Идентификатор объекта в указанном слое
  std::string ObjName;    //Имя объекта
};
typedef std::vector<struct Obj> TObjList;
```

#### Публичные методы
6.1. _GetStringHintUnderCursor_ возвращает строку всплывающей подсказки, используя данные под курсором

Синтаксис:

```cpp
QString GetStringHintUnderCursor(QList<QGraphicsItem *> Arr)
```

6.2. _GetObjListUnderCursor_ возвращает список объектов, используя данные под курсором

Синтаксис:

```cpp
TObjList GetObjListUnderCursor(QList<QGraphicsItem *> Arr)
```

6.3. _RePaint_ быстро перерисовать картографические данные

Синтаксис:

```cpp
void RePaint(void)
```

6.4. _CoolRePaint_ перерисовать картографические данные путем удаления и создания объектов слоев

Синтаксис:

```cpp
void CoolRePaint(void)
```

6.5. _WhatIsShow_ устанавливает признаки отображения тех или иных типов картографических данных

Синтаксис:

```cpp
void WhatIsShow(bool _Frame, bool _Grid15)
```

6.6. _GetLayerList_ возвращает список слоев

Синтаксис:

```cpp
TLayerList GetLayerList(void)
```

6.7. _ShowLayer_ показать слой, обратившись к нему по имени

Синтаксис:

```cpp
bool ShowLayer(std::string Name)
```

6.8. _HideLayer_ скрыть слой, обратившись к нему по имени

Синтаксис:

```cpp
bool HideLayer(std::string Name)
```

6.9. _AddLayer_ добавить новый слой, задав ему имя

Синтаксис:

```cpp
bool AddLayer(std::string Name)
```

6.10. _DelLayer_ удалить существующий слой, обратившись к нему по имени

Синтаксис:

```cpp
bool DelLayer(std::string Name)
```

6.11. _DelAllUserLayers_ удаляет все пользовательские слои и перерисовывает карту

Синтаксис:

```cpp
void DelAllUserLayers(void)
```

6.12. _AddLayerFromMIF_ добавить новый слой, создав его из MIF-файла формата MapInfo

На вход подаются:

  - имя слоя;
  - путь и имя MIF-файла.

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки.

Синтаксис:

```cpp
bool AddLayerFromMIF(std::string LayerName, std::string FilePathName)
```

6.13. _AddLayerDymanicPoint_ добавить новый слой, содержащий данные по часто перерисовываемым точечным объектам

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки

Синтаксис:

```cpp
bool AddLayerDynamicPoint(void)
```

6.14. _GetFreeID_ возвращает минимальное свободное значение идентификатора для размещения нового объекта в слое. 

Обращается к слою по имени

На выходе можно получить:

  - свободное значение идентификатора объекта.

Синтаксис:

```cpp
unsigned int GetFreeID(std::string Name)
```

6.15. _GetObjList_ возвращает список заголовков объектов в существующем слое

Обращается к слою по имени

На вход подаются:

  - имя слоя.

На выходе можно получить:

  - список заголовков объектов в указанном слое.

Синтаксис:

```cpp
TLayer::THeadersObjects GetObjList(std::string Name)
```

6.16. _AddInDynamicPoint_ добавляет в слой с динамическими точками новый объект

Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint.

На вход подаются:

  - идентификатор объекта;
  - описание объекта;
  - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад];
  - код цвета MapInfo.

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки

Синтаксис:

```cpp
bool AddInDynamicPoint(unsigned int ID, std::string Comment, 
                       TOnePoint Point, int ColorMI)
```

6.17. _MoveInDynamicPoint_ быстро сдвигает объект в слое с динамическими точками

На вход подаются:

  - идентификатор объекта;
  - описание объекта;
  - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад]

Синтаксис:

```cpp
void MoveInDynamicPoint(unsigned int ID, std::string Comment, TOnePoint Point)
```

6.18. _AddPointInLayer_ добавляет в существующий слой объект типа "точка" 

Обращается к слою по имени. Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint.

На вход подаются:

  - имя слоя;
  - идентификатор объекта;
  - наименование объекта;
  - тип символа, изображающего объект "точка";
  - геодезические координаты объекта "точка" на эллипсоиде ПЗ-90 [рад];
  - перо для рисования объекта "точка";
  - заливка для рисования объекта "точка".

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки.

Синтаксис:

```cpp
bool AddPointInLayer(std::string Name, unsigned int ID, std::string ObjName, 
                     TLayer::TTypeSymbol Type, TOnePoint Point, 
                     QPen Pen, QBrush Brush)
```

6.19. _AddPolyLineInLayer_ добавляет в существующий слой объект типа "полилиния"

Обращается к слою по имени. Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint.

На вход подаются:

  - имя слоя;
  - идентификатор объекта;
  - наименование объекта;
  - геодезические координаты узловых точек полилинии на эллипсоиде ПЗ-90 [рад];
  - перо для рисования объекта "полилиния".

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки.

Синтаксис:

```cpp
bool AddPolyLineInLayer(std::string Name, unsigned int ID, 
                        std::string ObjName, TSpot Spot, QPen Pen)
```

6.20. _AddRegionInLayer_ добавляет в существующий слой объект типа "регион"

Обращается к слою по имени. Добавление объекта в слой не вызывает перерисовку слоя. Следует пользоваться методом RePaint.

На вход подаются:

  - имя слоя;
  - идентификатор объекта;
  - наименование объекта;
  - геодезические координаты узловых точек региона на эллипсоиде ПЗ-90 [рад];
  - перо для рисования объекта "регион";
  - заливка для рисования объекта "регион".

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки.

Синтаксис:

```cpp
bool AddRegionInLayer(std::string Name, unsigned int ID, std::string ObjName, 
                      TSpot Spot, QPen Pen, QBrush Brush)
```

6.21. _DelObjFromLayer_ удаляет объект любого типа из существующего слоя. Обращается к слою по имени

На вход подаются:

  - имя слоя;
  - идентификатор объекта.

На выходе можно получить:

  - true в случае успешного выполнения процедуры;
  - false в случае какой-либо ошибки.

Синтаксис:

```cpp
bool DelObjFromLayer(std::string Name, unsigned int ID)
```

6.22. _FindLayer_ найти слой, обратившись к нему по имени

На вход подаются:

  - имя слоя.

На выходе можно получить:

  - индекс слоя в массиве слоев, либо (-1), если такой слой не найден.

Синтаксис:

```cpp
int FindLayer(std::string Name)
```

---

