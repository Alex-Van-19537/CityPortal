# 🏙️ City Portal Application

> Модерна конзолна система за управление на градски ресурси, реализирана в C++

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Platform](https://img.shields.io/badge/platform-Linux%2FUnix-brightgreen.svg)](#)

---

## 📋 Описание

**City Portal** е конзолно приложение за управление на градски активи и ресурси. Предоставя интуитивен CLI интерфейс за администратори и граждани с пълна система за контрол на достъпа на основата на роли (RBAC).

Системата позволява управление на:
- 👥 **Потребители** — регистрация, администриране, управление на роли
- 🚘 **Превозни средства** — марка, модел, вид гориво, цена
- 🏠 **Недвижими имоти** — апартаменти, къщи, студиа, мезонети

Всички данни се съхраняват персистентно в CSV файлове. Базите данни се презареждат автоматично преди всяка операция за консистентност.

---

## 🎯 Главни Характеристики

### 🔐 Система за Контрол на Достъпа

#### Администратор (Admin)
- ✅ Управление на потребители (преглед с пълен профил, добавяне, изтриване)
- ✅ Промяна на дохода на потребител (не може да е отрицателен)
- ✅ Промяна на баланса на потребител (с потвърждение при отрицателна стойност)
- ✅ Приключване на месец — добавя дохода към баланса на всеки потребител
- ✅ Управление на превозни средства (списък, добавяне, изтриване)
- ✅ Управление на недвижими имоти (списък, добавяне, изтриване)

#### Гражданин (Citizen)
- ✅ Преглед на личния профил с притежавани активи
- ✅ Превозни средства: преглед за продажба, листване с цена, сваляне от продажба, закупуване
- ✅ Недвижими имоти: преглед за продажба, листване с цена, сваляне от продажба, закупуване

### 🗄️ Архитектура на Данните
- **Template-based Database** — универсален шаблонен клас `Database<T>` за всички типове
- **Abstract Entity Model** — полиморфен дизайн чрез абстрактния базов клас `Entry`
- **CSV Persistence** — лесно четене и писане на данни с разделител `;`
- **Auto-reload** — базите данни се презареждат преди всяка операция
- **Type-safe Operations** — enums за `Role`, `Fuel` и `EstateType`

---

## 📋 Технически Изисквания

### Предварителни Условия
- **C++17** или по-нова версия
- **CMake** версия 3.10 или по-нова
- **GCC/Clang** компилатор
- **Linux/Unix** операционна система

### Проверка на Версии
```bash
g++ --version          # Проверка на C++ версия
cmake --version        # Проверка на CMake версия
```

---

## 🚀 Инсталация и Билдване

### 1. Клониране на Репозиториума
```bash
git clone https://github.com/Alex-Van-19537/CityPortal.git
cd CityPortal
```

### 2. Създаване на Build Директория
```bash
mkdir build
cd build
```

### 3. Конфигуриране с CMake
```bash
cmake ..
```

### 4. Билдване
```bash
make
```

### 5. Запуск на Приложението
```bash
./main
```

---

## 💻 Ръководство за Ползване

### Начален Екран
```
====================== City Portal Application ======================

1. Log In
0. Exit

Choice:
```

### Вход в Системата
1. Изберете опция **1** (Log In)
2. Въведете **username** и **password**
3. В зависимост от ролята ви ще видите Admin или Citizen меню

### Admin Меню

```
====================== Admin Menu ======================

1. Manage Users
2. Manage Vehicles
3. Manage Real Estate
0. Log Out
```

#### Manage Users
```
====================== Manage Users ======================

1. List users           - Преглед на всички потребители с пълни профили и активи
2. Add user             - Добавяне на нов потребител (fname, lname, username, password, age)
3. Change user income   - Промяна на месечния доход (не може да е отрицателен)
4. Change user balance  - Промяна на текущия баланс (изисква потвърждение при отрицателна стойност)
5. Delete user          - Изтриване на потребител по ID
6. Complete Month       - Добавя дохода към баланса на всеки потребител
0. Back
```

#### Manage Vehicles
```
====================== Manage Vehicles ======================

1. List Vehicles        - Преглед на всички превозни средства
2. Add Vehicle          - Добавяне (make, model, fuel, price); forSale = false по подразбиране
3. Delete vehicle       - Изтриване на превозно средство по ID
0. Back
```

#### Manage Real Estate
```
====================== Manage Real Estate ======================

1. List Real Estate     - Преглед на всички недвижими имоти
2. Add Real Estate      - Добавяне (type, address, size, price); forSale = false по подразбиране
3. Delete Real Estate   - Изтриване на недвижим имот по ID
0. Back
```

### Citizen Меню

```
====================== Citizen Menu ======================

1. View My Profile
2. Manage Vehicles
3. Manage Real Estate
0. Log Out
```

#### Manage Vehicles
```
====================== Manage Vehicles ======================

1. Get Vehicles for sale        - Преглед на превозни средства за продажба
2. Put Vehicle for sale         - Листване на собствено превозно средство с нова цена
3. Delist Vehicle from sale     - Сваляне от продажба на собствено превозно средство
4. Buy Vehicle                  - Закупуване на превозно средство
0. Back
```

#### Manage Real Estate
```
====================== Manage Real Estate ======================

1. Get Real Estate for sale     - Преглед на имоти за продажба
2. Put Real Estate for sale     - Листване на собствен имот с нова цена
3. Delist Real Estate from sale - Сваляне от продажба на собствен имот
4. Buy Real Estate              - Закупуване на недвижим имот
0. Back
```

### Примерен Профил
```
[ID]  [Firstname]     [Lastname]      [Username]        [Password]           [Age] [Income]  [Money]   [Role]
============================================================================================================
1     Alexander       Vankov          alex_v            securepass123        25    50000     250000    Admin
............................................................................................................

🚘 Vehicles:
[ID]  [Make]          [Model]         [Fuel]    [Price] [For Sale]
==================================================================
1     Toyota          Corolla         Petrol    15000   false
-----------------------------------------------------------------

🏠 Real Estate:
[ID]  [Type]          [Address]                                   [Size]    [Price] [For Sale]
==============================================================================================
1     Apartment       123 Main St, Sofia                          85        180000  false
----------------------------------------------------------------------------------------------
```

---

## 🔄 Marketplace — Покупко-продажба

Гражданите могат да търгуват директно помежду си:

1. Продавачът избира **Put Vehicle/Real Estate for sale**, въвежда ID на актива и задава цена (не може да е отрицателна).
2. Купувачът разглежда наличните оферти с **Get Vehicles/Real Estate for sale**.
3. Купувачът избира **Buy Vehicle/Buy Real Estate** и въвежда ID.
4. Системата автоматично:
   - Прехвърля парите от купувача към продавача
   - Актуализира списъците с активи и на двамата
   - Маркира актива като `forSale = false`
   - Записва всички промени в CSV файловете

> ⚠️ Транзакцията се отказва, ако:
> - Купувачът няма достатъчно средства
> - Потребителят вече е собственик на актива
> - Активът не е маркиран за продажба
> - Активът не съществува

---

## 📁 Структура на Проекта

```
CityPortal/
├── CMakeLists.txt              # Конфигурация за билдване
├── Containerfile               # Docker конфигурация
├── README.md                   # Документация
├── main.cpp                    # Входна точка — инициализира DB и стартира менюто
│
├── include/                    # Хедър файлове
│   ├── database.hpp            # Template Database<T> клас
│   ├── entry.hpp               # Abstract базов клас Entry
│   ├── menu.hpp                # Декларации на функциите за менютата
│   ├── user.hpp                # User клас + enum Role
│   ├── user_service.hpp        # User помощни функции (buy, completeMonth и др.)
│   ├── vehicle.hpp             # Vehicle клас + enum Fuel
│   ├── vehicle_service.hpp     # Vehicle помощни функции
│   ├── real_estate.hpp         # RealEstate клас + enum EstateType
│   └── real_estate_service.hpp # RealEstate помощни функции
│
├── src/                        # Имплементационни файлове
│   ├── entry.cpp               # Entry методи + оператори << и >>
│   ├── menu.cpp                # Логика на всички менюта (Login, Admin, Citizen)
│   ├── user.cpp                # User методи, CSV четене/писане
│   ├── user_service.cpp        # completeMonth, buyRealEstate, buyVehicle, print функции
│   ├── vehicle.cpp             # Vehicle методи, CSV четене/писане
│   ├── vehicle_service.cpp     # getAllVehicles, getVehiclesForSale
│   ├── real_estate.cpp         # RealEstate методи, CSV четене/писане
│   └── real_estate_service.cpp # getAllRE, getRealEstateForSale
│
└── data/                       # Данни (CSV файлове)
    ├── users.csv
    ├── vehicles.csv
    └── real_estate.csv
```

---

## 🏛️ Архитектура

Проектът следва 3-слойна архитектура:

- **Слой 1 — CLI интерфейс:** `menu.cpp` — навигация, вход/изход, четене на потребителски вход
- **Слой 2 — Application Logic:** RBAC проверка в `main.cpp` + бизнес логика в `*_service.cpp` файловете
- **Слой 3 — Данни:** шаблонният `Database<T>` + CSV файлове

### Основни Концепции

- **Template Database**: `Database<T>` работи с всеки тип, наследяващ `Entry`. Поддържа `add`, `remove`, `find` (с lambda predicate), `list`, `save`, `load`, `reload`.
- **Polymorphism**: `Entry` дефинира чисто виртуален интерфейс (`writeToCSV`, `loadFromCSV`, `ins`, `ext`). Операторите `<<` и `>>` са дефинирани веднъж в базовия клас и делегират към виртуалните методи.
- **Role-Based Access Control**: `main.cpp` проверява `currentUser->getRole()` и насочва към `enterAdminMenu` или `enterCitizenMenu`.
- **CSV Persistence**: Всеки файл започва с `nextId`, следван от записите разделени с `;`.
- **Auto-reload**: `usersDB.reload()`, `vehiclesDB.reload()` и `real_estateDB.reload()` се извикват преди всяка операция в менютата.

---

## 🔧 Детайли на Същностите

### User (Потребител)
| Свойство | Тип | Описание |
|----------|-----|---------|
| id | int | Уникален идентификатор |
| firstname | string | Име |
| lastname | string | Фамилия |
| username | string | Потребителско име |
| password | string | Парола |
| age | int | Възраст |
| income | int | Месечен доход (добавя се при Complete Month) |
| money | int | Текущ баланс |
| role | Role | `Admin` или `Citizen` |
| vehicles | vector\<int\> | ID-та на притежавани превозни средства |
| real_estate | vector\<int\> | ID-та на притежавани имоти |

### Vehicle (Превозно Средство)
| Свойство | Тип | Описание |
|----------|-----|---------|
| id | int | Уникален идентификатор |
| make | string | Марка (Toyota, BMW и т.н.) |
| model | string | Модел (Corolla, X5 и т.н.) |
| fuel | Fuel | `Petrol`, `Diesel` или `LPG` |
| price | int | Цена |
| forSale | bool | Налично ли е за продажба (по подразбиране `false`) |

### RealEstate (Недвижимост)
| Свойство | Тип | Описание |
|----------|-----|---------|
| id | int | Уникален идентификатор |
| estateType | EstateType | `Apartment`, `House`, `Studio`, `Maisonette` |
| address | string | Адрес |
| size | int | Площ в кв.м |
| price | int | Цена |
| forSale | bool | Налично ли е за продажба (по подразбиране `false`) |

---

## 📦 CSV Формат

Всеки файл започва с ред `nextId`, последван от записите. Полетата са разделени с `;`.

### users.csv
```
nextId
1;Alexander;Vankov;alex_v;securepass123;25;50000;250000;2,3;1,2;Admin
2;John;Doe;john_d;password456;30;40000;0;;;Citizen
```
> Полетата за `real_estate` и `vehicles` са ID-та, разделени със запетая. Оставят се празни, ако потребителят няма активи.

### vehicles.csv
```
nextId
1;Toyota;Corolla;Petrol;15000;0
2;BMW;X5;Diesel;45000;1
```

### real_estate.csv
```
nextId
1;Apartment;123 Main St Sofia;85;180000;0
2;House;456 Oak Ave Sofia;200;350000;1
```

---

## 🚦 Примерен Работен Процес

### 1. Логване като Администратор
```
Choice: 1
Username: alex_v
Password: securepass123
🥹  Welcome back, alex_v!
```

### 2. Добавяне на Нов Потребител
```
Choice: 1  // Manage Users
Choice: 2  // Add user
Firstname: Maria
Lastname: Petrova
Username: maria_p
Password: mypassword123
Age: 28
✅ [Success]: User added with ID: 3!
```

### 3. Добавяне на Превозно Средство
```
Choice: 2  // Manage Vehicles
Choice: 2  // Add Vehicle
Make: Mercedes
Model: E-Class
Fuel [ Petrol, Diesel, LPG ]: Diesel
Price: 55000
✅ [Success]: Vehicle added with ID: 3!
```

### 4. Добавяне на Недвижим Имот
```
Choice: 3  // Manage Real Estate
Choice: 2  // Add Real Estate
Type [Apartment, House, Studio, Maisonette]: House
Address: 12 Rose Street Sofia
Size [m2]: 150
Price: 320000
✅ [Success]: Real Estate added with ID: 2!
```

### 5. Приключване на Месец
```
Choice: 1  // Manage Users
Choice: 6  // Complete Month
[Success] Completing month!
// Доходът на всеки потребител се добавя към баланса му
```

### 6. Закупуване на Имот като Гражданин
```
Choice: 3   // Manage Real Estate
Choice: 1   // Get Real Estate for sale
Choice: 4   // Buy Real Estate
Real Estate to buy[ID]: 2
[Success] Transaction is successful and Real Estate with ID [2] is yours!
```

---

## 🛡️ Бележки за Безопасност

⚠️ **Известни Ограничения**
- Паролите се съхраняват в обикновен текст — за production се препоръчва хеширане (bcrypt)
- Входните данни не се валидират напълно — препоръчва се добавяне на проверки
- CSV файловете не са криптирани — чувствителните данни са четими

---

## 🔄 Статус на Проекта

- ✅ Core функционалност (Users, Vehicles, RealEstate)
- ✅ Role-Based Access Control с подменюта
- ✅ CSV persistence с auto-reload
- ✅ Marketplace (покупко-продажба между потребители)
- ✅ Complete Month (начисляване на доход)
- ✅ Промяна на доход и баланс от администратор (с валидация за отрицателни стойности)
- 🔄 Изтриване на потребители, превозни средства и имоти
- 🔄 Input validation и санитизация
- 🔄 Error handling
- ⏳ Unit tests
- ⏳ Enhanced security (password hashing)

### Планирани Функции
- [ ] Хеширане на пароли (bcrypt)
- [ ] Пълна валидация и санитизация на входа
- [ ] Логване на активности (audit log)

---

<div align="center">

**Направено с ❤️ в България**

</div>
