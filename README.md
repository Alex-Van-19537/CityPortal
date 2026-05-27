# 🏙️ City Portal Application

> Модерна конзолна система за управление на градски ресурси, реализирана в C++

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Platform](https://img.shields.io/badge/platform-Linux%2FUnix-brightgreen.svg)](#)

---

## 📋 Описание

**City Portal** е мощно конзолно приложение за управление на градски активи и ресурси. Предоставя интуитивен интерфейс за администратори и граждани с пълна система за контрол на достъпа на основата на роли.

Системата позволява управление на:
- 👥 **Потребители** — регистрация, администриране, управление на роли
- 🚘 **Превозни средства** — марка, модел, вид гориво, цена
- 🏠 **Недвижими имоти** — апартаменти, къщи, студиа, мезонети

Всички данни се съхраняват персистентно в CSV файлове за дълготрайност.

---

## 🎯 Главни Характеристики

### 🔐 Система за Контрол на Достъпа

#### Администратор (Admin)
- ✅ Преглед на всички потребители с детайли
- ✅ Добавяне и изтриване на потребители
- ✅ Управление на превозни средства (CRUD операции)
- ✅ Управление на недвижими имоти (CRUD операции)
- ✅ Преглед на всички активи в системата
- ✅ Приключване на месец (добавя дохода към баланса на всички потребители)

#### Гражданин (Citizen)
- ✅ Преглед на личния профил с активи
- ✅ Преглед на превозни средства за продажба
- ✅ Листване и сваляне от продажба на собствени превозни средства
- ✅ Закупуване на превозни средства
- ✅ Преглед на недвижими имоти за продажба
- ✅ Листване и сваляне от продажба на собствени недвижими имоти
- ✅ Закупуване на недвижими имоти

### 🗄️ Архитектура на Данните
- **Template-based Database** — универсална система за управление на данни
- **Abstract Entity Model** — полиморфен дизайн за всички сущности
- **CSV Persistence** — лесна четене и писане на данни
- **Type-safe Operations** — използване на enums за статични данни

---

## 📋 Технически Изисквания

### Предварителни Условия
- **С++17** или по-нова версия
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
3. В зависимост от ролята ви ще видите съответното меню

### Admin Меню
```
1.  List users          - Преглед всички потребители с профили
2.  Add user            - Добавяне нов потребител
3.  Delete user         - Изтриване на потребител по ID
4.  List Vehicles       - Преглед на всички превозни средства
5.  Add Vehicle         - Добавяне на превозно средство
6.  Delete vehicle      - Изтриване на превозно средство по ID
7.  List Real Estate    - Преглед на всички недвижими имоти
8.  Add Real Estate     - Добавяне на недвижим имот
9.  Delete Real Estate  - Изтриване на недвижим имот по ID
10. Complete Month      - Добавя дохода към баланса на всеки потребител
0.  Log Out             - Изход
```

### Citizen Меню
```
1. View My Profile              - Профил с притежавани активи
2. Get Vehicles for sale        - Преглед на превозни средства за продажба
3. Put Vehicle for sale         - Листване на собствено превозно средство
4. Delist Vehicle from sale     - Сваляне от продажба на превозно средство
5. Buy Vehicle                  - Закупуване на превозно средство
6. Get Real Estate for sale     - Преглед на имоти за продажба
7. Put Real Estate for sale     - Листване на собствен имот
8. Delist Real Estate from sale - Сваляне от продажба на имот
9. Buy Real Estate              - Закупуване на недвижим имот
0. Log Out                      - Изход
```

### Примерен Профил
```
[ID]  [Firstname]     [Lastname]      [Username]        [Password]           [Age] [Income]  [Money]  [Role]
============================================================================================================
1     Alexander       Vankov          alex_v            securepass123        25    50000     250000   Admin
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

1. Продавачът избира **Put Vehicle/Real Estate for sale** и въвежда ID на актива.
2. Купувачът разглежда наличните оферти с **Get Vehicles/Real Estate for sale**.
3. Купувачът избира **Buy Vehicle/Buy Real Estate** и въвежда ID.
4. Системата автоматично прехвърля парите, актуализира собствеността и записва промените в CSV файловете.

> ⚠️ Транзакцията се отказва, ако купувачът няма достатъчно средства или ако потребителят вече е собственик на актива.

---

## 📁 Структура на Проекта

```
CityPortal/
├── CMakeLists.txt              # Конфигурация за билдване
├── Containerfile               # Docker конфигурация
├── README.md                   # Документация
├── main.cpp                    # Главна логика и менюта
│
├── include/                    # Хедър файлове
│   ├── database.hpp            # Template Database клас
│   ├── entry.hpp               # Abstract базов клас
│   ├── user.hpp                # User клас
│   ├── user_service.hpp        # User помощни функции
│   ├── vehicle.hpp             # Vehicle клас
│   ├── vehicle_service.hpp     # Vehicle помощни функции
│   └── real_estate.hpp         # RealEstate клас
│   └── real_estate_service.hpp # RealEstate помощни функции
│
├── src/                        # Имплементационни файлове
│   ├── entry.cpp
│   ├── user.cpp
│   ├── user_service.cpp
│   ├── vehicle.cpp
│   ├── vehicle_service.cpp
│   ├── real_estate.cpp
│   └── real_estate_service.cpp
│
└── data/                       # Данни (CSV файлове)
    ├── users.csv
    ├── vehicles.csv
    └── real_estate.csv
```

---

## 🏛️ Архитектура

### Основни Концепции

- **Template Database**: Универсална система за управление на всички типове данни
- **Polymorphism**: Всяка същност наследява от `Entry` за единообразна обработка
- **Role-Based Access Control**: Разлики в достъпа според ролята на потребителя
- **CSV Persistence**: Данните се запазват между сесиите

---

## 🔧 Детайли на Сущностите

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
| money | unsigned | Текущ баланс |
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
| forSale | bool | Налично ли е за продажба |

### RealEstate (Недвижимост)
| Свойство | Тип | Описание |
|----------|-----|---------|
| id | int | Уникален идентификатор |
| estateType | EstateType | `Apartment`, `House`, `Studio`, `Maisonette` |
| address | string | Адрес |
| size | int | Площ в кв.м |
| price | int | Цена |
| forSale | bool | Налично ли е за продажба |

---

## 📦 CSV Формат

Всеки файл започва с ред `nextId`, последван от записите. Полетата са разделени с `;`.

### users.csv
```
nextId
1;Alexander;Vankov;alex_v;securepass123;25;50000;250000;2,3;1,2;Admin
2;John;Doe;john_d;password456;30;40000;0;;3;Citizen
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
🥹 Welcome back, alex_v!
```

### 2. Добавяне на Нов Потребител
```
Choice: 2
Firstname: Maria
Lastname: Petrova
Username: maria_p
Password: mypassword123
Age: 28
✅ [Success]: User added with ID: 3!
```

### 3. Добавяне на Превозно Средство
```
Choice: 5
Make: Mercedes
Model: E-Class
Fuel [ Petrol, Diesel, LPG ]: Diesel
Price: 55000
✅ [Success]: Vehicle added with ID: 3!
```

### 4. Приключване на Месец
```
Choice: 10
[Success] Completing month!
// Доходът на всеки потребител се добавя към баланса му
```

### 5. Закупуване на Имот като Гражданин
```
Choice: 6   // Преглед на имоти за продажба
Choice: 9   // Купуване
Real Estate to buy[ID]: 2
[Success] Transaction is successful and Real Estate with ID [2] is yours!
```

---

## 🛡️ Бележки за Безопасност

⚠️ **Известни Ограничения**
- Паролите се съхраняват в обикновен текст — за production се препоръчва хеширане (bcrypt)
- Входните данни не се валидират — препоръчва се добавяне на проверки
- CSV файловете не са криптирани — чувствителните данни са четими

---

## 🔄 Статус на Проекта

- ✅ Core функционалност (Users, Vehicles, RealEstate)
- ✅ Role-Based Access Control
- ✅ CSV persistence
- ✅ Marketplace (покупко-продажба между потребители)
- ✅ Complete Month (начисляване на доход)
- 🔄 Input validation и санитизация
- 🔄 Error handling
- ⏳ Unit tests
- ⏳ Enhanced security (password hashing)

### Планирани Функции
- [ ] Хеширане на пароли (bcrypt)
- [ ] Валидация и санитизация на входа
- [ ] Логване на активности (audit log)

---

<div align="center">

**Направено с ❤️ в България**

</div>
