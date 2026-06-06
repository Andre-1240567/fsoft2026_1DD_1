# US1 - Specify Vaccine Type
##  Description
As Administrator, I want to specify a new vaccine type so that it can be used in the vaccination catalog.

##  Acceptance Criteria
- [ ] Record the vaccine type code (unique).
- [ ] Record the disease it prevents.
- [ ] **Technology Selection:** The technology must be selected from a predefined list of available types (e.g., mRNA, Viral Vector, Inactivated Virus, etc.).
- [ ] *Reference:* Based on Pfizer's vaccine technology guide (https://www.pfizer.com/news/articles/understanding_six_types_of_vaccine_technologies).
- [ ] Record the recovery period (in minutes).
- [ ] All data must be persisted.

## Domain Entities Involved
- `VaccineType`
- `CenterAdministrator`

---

# US2 - Register a vaccine
## Description
As Administrator, I want to register a vaccine (physical lot) to be stored in the center's inventory.

## Acceptance Criteria
- [ ] Link the vaccine to an existing `VaccineType` (which already defines the technology).
- [ ] Record the commercial name (e.g., Comirnaty) and brand (e.g., Pfizer).
- [ ] Record the lot number and expiration date.
- [ ] Record the initial quantity of doses available in this lot.
- [ ] Ensure the vaccine is correctly added to the Healthcare Center's stock.

## Domain Entities Involved
- `Vaccine`
- `VaccineType` (Association)
- `HealthcareCenter`

---
# US3 - Register an employee

## Description
As Administrator, I want to register a new employee and assign them a specific role.

##  Acceptance Criteria
- [ ] Assign a single role: Center Administrator, Nurse, or Receptionist.
- [ ] Mandatory fields: Name, Phone Number, and E-mail Address.
- [ ] Validate Phone Number and Citizen Card Number (Portuguese format).
- [ ] Ensure Phone Number and E-mail Address are unique in the system.

## Technical Notes
- **Implementation Strategy:** Although the system allows registering multiple Administrators, for the current prototype we will focus on having at least one functional Admin to manage the center.
- **Constraints:** If the team decides to limit to 1 Admin in the code, ensure the error message is clear, but keep the data structure flexible as per the Domain Model.

## Domain Entities Involved
- `Employee` (and its subclasses)

---

# US4 - List employees by function/role
## Description
As Administrator, I want to get a list of employees assigned to a specific function/role.

## Acceptance Criteria
- [ ] Prompt the user to select or specify a role (e.g., Nurse).
- [ ] Display a list of all employees assigned to that role.
- [ ] Output includes relevant contact and identification details.

## Domain Entities Involved
- `Employee` (Subclasses)
---
# US5 - List all vaccines
## Description
As Administrator, I want to get a list of all vaccines in the system, grouped by their type and sorted by brand.

## Acceptance Criteria
- [ ] Group the vaccines by their `VaccineType` (e.g., all COVID-19 vaccines together).
- [ ] Within each group, list the vaccines alphabetically by **Brand** .
- [ ] Display the following information for each vaccine: Commercial Name, Lot Number, Expiration Date, and Quantity.
- [ ] If no vaccines are registered, display a clear "No inventory found" message.

## Technical Notes
- **Sorting Logic:** Requires a sorting algorithm (like `std::sort`) with a custom comparator or a structured data approach (like a `std::map<VaccineType*, std::vector<Vaccine*>>`).
- **UI:** The output should be clear, using headers for each Vaccine Type.

## Domain Entities Involved
- `Vaccine`
- `VaccineType`
- `HealthcareCenter` (Inventory)

---
# US6 - Register an SNS user
## Description
As Receptionist, I want to register a new SNS user in the system so that they can be scheduled for vaccination.

## Acceptance Criteria
- [ ] Mandatory fields: Name, Address, Phone Number, SNS User Number, CC Number, and Birth Date.
- [ ] **Optional field:** Sex (the user can choose not to provide this info).
- [ ] **Validation (PT Format):** Phone Number and Citizen Card (CC) Number must follow Portuguese standards.
- [ ] **Uniqueness:** The Phone Number and SNS User Number must be unique (no two users can have the same).
- [ ] Data must be correctly persisted in the system.

## Technical Notes
- **Actor:** This functionality is specific to the `Receptionist` role.
- **Validation Logic:** Reuse the validation functions from the `Utils` task
- **Sex Attribute:** Can be implemented as a nullable string, an Enum (Male, Female, Other, NotSpecified), or a char.

## Domain Entities Involved
- `SNSUser`
- `Receptionist`
- `HealthcareCenter`

---
# US7 - Schedule a vaccine administration (Receptionist)
## Description
As a Receptionist, I want to schedule a vaccine administration for an SNS user

## Acceptance Criteria
- [ ] The Receptionist must be able to search for/identify the **SNS User** (via SNS User Number).
- [ ] The system must verify if the user exists (US6).
- [ ] The Receptionist selects the **Vaccine Type**.
- [ ] The Receptionist selects the **Date** and **Time** for the appointment.
- [ ] **Conflict Check:** (Optional/Recommended) The system should check if the user already has a pending appointment for that vaccine type.
- [ ] **Confirmation:** The system confirms the schedule and associates it with the SNS User.

## 🛠 Technical Notes
- **Service Layer:** This US should call the appropriate method in `AppointmentController` (e.g., `createAppointment(snsNumber, vaccineType, date)`).
- **Actor:** Specific to the `Receptionist` role.

## Domain Entities Involved
- `Receptionist`
- `SNSUser`
- `VaccineType`
- `Appointment`
---
# US8 - Register SNS User Arrival
## Description
As a Receptionist, I want to register the arrival of an SNS user at the vaccination center so that they can be moved to the waiting room and subsequent administration.

## Acceptance Criteria
- [ ] Identify the user via their **SNS User Number**.
- [ ] **AC8.1:** Prevent duplicate entries for the same user on the same day (a user cannot "arrive" twice for the same appointment).
- [ ] **AC8.2:** Upon successful registration, the user must be assigned to the **Waiting Room**.
- [ ] The system should verify if the user has an appointment scheduled for the current date .

## Technical Notes
- **Waiting Room Logic:** This can be implemented as a `std::vector` or `std::queue` within the `HealthcareCenter` or a specific `VaccinationCenter` class.
- **Date Validation:** Use the system clock to capture the arrival time and compare it with the appointment date.
- **Status Update:** Consider adding a `status` attribute to the `Appointment` class (e.g., `SCHEDULED`, `WAITING`, `COMPLETED`).

## Domain Entities Involved
- `Receptionist`
- `SNSUser`
- `Appointment`
- `WaitingRoom` 
---
# US9 - Consult SNS Users in the Waiting Room
## Description
As a Nurse, I want to consult the list of SNS users currently in the waiting room so that I can call the next user for vaccine administration.

## Acceptance Criteria
- [ ] Display the list of users present in the Waiting Room.
- [ ] Users must be listed in a First-Come, First-Served (FIFO) order.
- [ ] Display the SNS User Number and Name for each user.
- [ ] If the waiting room is empty, display a clear message indicating so.

## Technical Notes
- **Waiting Room Logic:** Pull data from the `HealthcareCenter`'s `waitingRoom` container.
- **Actor:** Specific to the `Nurse` role.

## Domain Entities Involved
- `Nurse`
- `SNSUser`
- `HealthcareCenter` (Waiting Room container) 

---

# US10 - Record vaccine administration

## Description
As a Nurse, I want to record the administration of a vaccine to an SNS user so that the system tracks the vaccination history and ensures the user's safety during recovery.

## Acceptance Criteria
- [ ] **AC10.1:** The Nurse must select a **Vaccine** and the specific **Lot Number** administered (data from US2/US5).
- [ ] **AC10.2:** Upon recording, the SNS user must be moved from the "Waiting Room" to the **Recovery Room**.
- [ ] The system must record the **timestamp** of the administration.
- [ ] The system should update the status of the user's appointment to `ADMINISTERED`.

## Technical Notes
- **State Transition:** This US involves moving an `SNSUser` (or their `Appointment`) from the `waitingRoom` container to a `recoveryRoom` container.
- **Inventory Management:** (Optional but recommended) Decrease the available quantity of the selected vaccine lot.
- **Recovery Logic:** You might want to store the "Recovery End Time" (Admin Time + 30 minutes) to help the nurse monitor the room.
- **Validation:** Only users currently in the `Waiting Room` (US8/US9) can have a vaccine administration recorded.

## Domain Entities Involved
- `Nurse`
- `SNSUser`
- `Vaccine`
- `VaccineLot`
- `Appointment`
- `HealthcareCenter` (Recovery Room container)