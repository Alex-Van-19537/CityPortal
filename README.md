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

#### Гражданин (Citizen)
- ✅ Преглед на личния профил
- ✅ Просмотр на притежавани превозни средства
- ✅ Просмотр на притежавани недвижими имоти
- ✅ Информация за доход и възраст

### 🗄️ Архитектура на Данните
- **Template-based Database** — универсална система за управление на данни
- **Abstract Entity Model** — полиморфен дизайн за всички сущности
- **CSV Persistence** — лесна четене и писане на данни
- **Type-safe Operations** — използване на enums за stati данни

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
git clone https://github.com/yourusername/CityPortal.git
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
1. List users          - Преглед всички потребители
2. Add user            - Добавяне нов потребител
3. Delete user         - Изтриване потребител
4. List Vehicles       - Преглед превозни средства
5. Add Vehicle         - Добавяне превозно средство
6. Delete vehicle      - Изтриване превозно средство
7. List Real Estate    - Преглед недвижимости
8. Add Real Estate     - Добавяне недвижимост
9. Delete Real Estate  - Изтриване недвижимост
0. Log Out             - Изход
```

### Citizen Меню
```
1. View My Profile     - Преглед личен профил със активи
0. Log Out             - Изход
```

### Примерен Профил
```
[ID]  [Firstname]     [Lastname]      [Username]       [Password]           [Age][Income]  [Role]
==================================================================================================
1     Alexander       Vankov          alex_v           securepass123        25   50000     ADMIN
....................................................................................................

🚘 Vehicles:
[ID]  [Make]          [Model]         [Fuel]    [Price]
=====================================================
1     Toyota          Corolla         PETROL    15000

🏠 Real Estate:
[ID]  [Type]          [Address]                       [Size]    [Price]
======================================================================
1     APARTMENT       123 Main St, Sofia               85        180000
```

---

## 📁 Структура на Проекта

```
CityPortal/
├── CMakeLists.txt              # Конфигурация за bilding
├── Containerfile               # Docker конфигурация
├── README.md                   # Документация
├── main.cpp                    # Главна логика и менюта
│
├── include/                    # Хедър файлове
│   ├── database.hpp            # Template Database класа
│   ├── entry.hpp               # Abstract Entity базов клас
│   ├── user.hpp                # User класа
│   ├── vehicle.hpp             # Vehicle класа
│   └── real_estate.hpp         # RealEstate класа
│
├── src/                        # Имплементационни файлове
│   ├── entry.cpp               # Entry имплементация
│   ├── user.cpp                # User имплементация
│   ├── vehicle.cpp             # Vehicle имплементация
│   └── real_estate.cpp         # RealEstate имплементация
│
└── data/                       # Данни (CSV файлове)
    ├── users.csv               # Съхранени потребители
    ├── vehicles.csv            # Съхранени превозни средства
    └── real_estate.csv         # Съхранени недвижими имоти
```

---

## 🏛️ Архитектура

### Основни Концепции

- **Template Database**: Универсална система за управление на всички типове данни
- **Polymorphism**: Всяка сущност наследява от Entry за единообразна обработка
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
| income | int | Доход |
| role | Role | ADMIN или CITIZEN |
| vehicles | vector<int> | Списък на превозни средства |
| real_estate | vector<int> | Списък на имоти |

### Vehicle (Превозно Средство)
| Свойство | Тип | Описание |
|----------|-----|---------|
| id | int | Уникален идентификатор |
| make | string | Марка (Toyota, BMW и т.н.) |
| model | string | Модел (Corolla, X5 и т.н.) |
| fuel | Fuel | PETROL, DIESEL или LPG |
| price | int | Цена |

### RealEstate (Недвижимост)
| Свойство | Тип | Описание |
|----------|-----|---------|
| id | int | Уникален идентификатор |
| estateType | EstateType | APARTMENT, HOUSE, STUDIO, MAISONETTE |
| address | string | Адрес |
| size | int | Площ в кв.м |
| price | int | Цена |

---

## 📦 CSV Формат

### users.csv
```
nextId
1,Alexander,Vankov,alex_v,securepass123,25,50000,ADMIN,2;3,1;2
2,John,Doe,john_d,password456,30,40000,CITIZEN,1,3
```

### vehicles.csv
```
nextId
1,Toyota,Corolla,PETROL,15000
2,BMW,X5,DIESEL,45000
```

### real_estate.csv
```
nextId
1,APARTMENT,123 Main St Sofia,85,180000
2,HOUSE,456 Oak Ave Sofia,200,350000
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
✅ User added successfully!
```

### 3. Добавяне на Превозно Средство
```
Choice: 5
Make: Mercedes
Model: E-Class
Fuel: (1)PETROL (2)DIESEL (3)LPG: 2
Price: 55000
✅ Vehicle added successfully!
```

### 4. Преглед на Потребител като Гражданин
```
Choice: 1 (Log In)
Username: john_d
Password: password456
// Виждате вашия профил с активи
```

---

## 🛡️ Безопасност

⚠️ **Забележки за Безопасност**
- Паролите се съхраняват в обикновен текст. За производство се препоръчва хеширане (bcrypt)
- Входът не е валидиран. Препоръчва се добавяне на валидация
- Няма енкрипция на CSV файлове. Препоръчва се зашифроване на чувствителни данни

---

## 🔄 Развитие

### Текущ Статус
- ✅ Core функционалност (Users, Vehicles, RealEstate)
- ✅ Role-Based Access Control
- ✅ CSV persistence
- 🔄 Input validation
- 🔄 Error handling
- ⏳ Unit tests
- ⏳ Enhanced security

### Планирани Функции
- [ ] Пароли с хеширане (bcrypt)
- [ ] Input validation и санитизация
- [ ] Логване на активности

<div align="center">

**Направено с ❤️ в България**

</div>
