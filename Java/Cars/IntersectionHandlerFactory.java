package com.apd.tema2.factory;

import static java.lang.Thread.sleep;

import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.IntersectionHandler;

/**
 * Clasa Factory ce returneaza implementari ale InterfaceHandler sub forma unor
 * clase anonime.
 */
public class IntersectionHandlerFactory {

	public static IntersectionHandler getHandler(String handlerType) {
		// simple semaphore intersection
		// max random N cars roundabout (s time to exit each of them)
		// roundabout with exactly one car from each lane simultaneously
		// roundabout with exactly X cars from each lane simultaneously
		// roundabout with at most X cars from each lane simultaneously
		// entering a road without any priority
		// crosswalk activated on at least a number of people (s time to finish all of
		// them)
		// road in maintenance - 2 ways 1 lane each, X cars at a time
		// road in maintenance - 1 way, M out of N lanes are blocked, X cars at a time
		// railroad blockage for s seconds for all the cars
		// unmarked intersection
		// cars racing
		// IntersectionHandler intersection;
		IntersectionHandler handler;
		switch (handlerType) {
			case "simple_semaphore":
				handler = new IntersectionHandler() {
					@Override
					public void handle(Car car) {
						System.out.println("Car " + car.getId() + " has reached the semaphore, now waiting...");
						try {
							Thread.currentThread().sleep(car.getWaitingTime());
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						System.out.println("Car " + car.getId() + " has waited enough, now driving...");
					}
				};
			case "simple_n_roundabout":
				handler = new IntersectionHandler() {
					@Override
					public void handle(Car car) {

					}
				};
			case "simple_strict_1_car_roundabout":
				handler = new IntersectionHandler() {
					@Override
					public void handle(Car car) {

					}
				};
			case "simple_strict_x_car_roundabout":
				handler = new IntersectionHandler() {
					@Override
					public void handle(Car car) {

					}
				};
			case "simple_max_x_car_roundabout":
				handler = new IntersectionHandler() {
					@Override
					public void handle(Car car) {
						// Get your Intersection instance

						try {
							sleep(car.getWaitingTime());
						} catch (InterruptedException e) {
							e.printStackTrace();
						} // NU MODIFICATI

						// Continuati de aici
					}
				};
			case "priority_intersection":
				handler = new IntersectionHandler() {
					@Override
					public void handle(Car car) {
						// Get your Intersection instance

						try {
							sleep(car.getWaitingTime());
						} catch (InterruptedException e) {
							e.printStackTrace();
						} // NU MODIFICATI

						// Continuati de aici
					}
				};
			case "crosswalk":
				handler = new IntersectionHandler() {
					@Override
					public void handle(Car car) {

					}
				};
			case "simple_maintenance":
				handler = new IntersectionHandler() {
					@Override
					public void handle(Car car) {

					}
				};
			case "complex_maintenance":
				handler = new IntersectionHandler() {
					@Override
					public void handle(Car car) {

					}
				};
			case "railroad":
				handler = new IntersectionHandler() {
					@Override
					public void handle(Car car) {

					}
				};
			default:
				handler = null;
		}
		;
		return handler;
	}
}
